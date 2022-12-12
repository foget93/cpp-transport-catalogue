#include "svg.h"

using namespace std::literals;

std::ostream& operator<<(std::ostream &out, svg::StrokeLineCap line_cap) {
  using svg::StrokeLineCap;

  switch (line_cap) {
    case StrokeLineCap::BUTT:
      out << "butt"sv;
      break;
    case StrokeLineCap::ROUND:
      out << "round"sv;
      break;
    case StrokeLineCap::SQUARE:
      out << "square"sv;
      break;
    default:
      throw std::logic_error("Not implemented"s);
  }
  return out;
}

std::ostream& operator<<(std::ostream &out, svg::StrokeLineJoin line_join) {
  using svg::StrokeLineJoin;

  switch (line_join) {
    case StrokeLineJoin::ARCS:
      out << "arcs"sv;
      break;
    case StrokeLineJoin::BEVEL:
      out << "bevel"sv;
      break;
    case StrokeLineJoin::MITER:
      out << "miter"sv;
      break;
    case StrokeLineJoin::MITER_CLIP:
      out << "miter-clip"sv;
      break;
    case StrokeLineJoin::ROUND:
      out << "round"sv;
      break;
    default:
      throw std::logic_error("Not implemented"s);
  }
  return out;
}

std::ostream& operator<<(std::ostream &out, svg::Color color) {
  visit(svg::ColorPrintVisitor { out }, color);
  return out;
}

namespace svg {

using namespace std::literals;


void ColorPrintVisitor::operator()(std::monostate) {
    out_ << "none"sv;
}
void ColorPrintVisitor::operator()(std::string &str) {
    out_ << str;
}
void ColorPrintVisitor::operator()(Rgb color) {
    out_ << "rgb("sv << static_cast<int>(color.red) << ','
        << static_cast<int>(color.green) << ',' << static_cast<int>(color.blue)
        << ')';
}
void ColorPrintVisitor::operator()(Rgba color) {
    out_ << "rgba("sv << static_cast<int>(color.red) << ','
        << static_cast<int>(color.green) << ',' << static_cast<int>(color.blue)
        << ',' << color.opacity << ')';
}


void Object::Render(const RenderContext& context) const {
    context.RenderIndent();

    // Делегируем вывод тега своим подклассам
    RenderObject(context);

    context.out << std::endl;
}

// ---------- Circle ------------------

Circle& Circle::SetCenter(Point center)  {
    center_ = center;
    return *this;
}

Circle& Circle::SetRadius(double radius)  {
    radius_ = radius;
    return *this;
}

void Circle::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
    out << "r=\""sv << radius_ << "\" "sv;
    this->PathProps::RenderAttrs(out); // атрибутики хитро
    out << "/>"sv;
}

// ---------- Polyline ----------------

Polyline& Polyline::AddPoint(Point point) {
    points_.push_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext& context) const {
    /*<polyline points="0,100 50,25 50,75 100,0" />*/
    auto& out = context.out;
    out << "<polyline points=\""sv;
    for (auto it = points_.begin(); it != points_.end(); ++it) {
        out << it->x << ","sv << it->y;
        if (it + 1 != points_.end()) {
            out << " "sv;
        }
    }
    out << "\" "sv;
    this->PathProps::RenderAttrs(out);
    out << "/>"sv;
}

// ---------- Text --------------------

// Задаёт координаты опорной точки (атрибуты x и y)
Text& Text::SetPosition(Point pos) {
    pos_ = pos;
    return *this;
}

// Задаёт смещение относительно опорной точки (атрибуты dx, dy)
Text& Text::SetOffset(Point offset) {
    offset_ = offset;
    return *this;
}

// Задаёт размеры шрифта (атрибут font-size)
Text& Text::SetFontSize(uint32_t size) {
    font_size_ = size;
    return *this;
}

// Задаёт название шрифта (атрибут font-family)
Text& Text::SetFontFamily(std::string font_family) {
    font_family_ = font_family;
    return *this;
}

// Задаёт толщину шрифта (атрибут font-weight)
Text& Text::SetFontWeight(std::string font_weight) {
    font_weight_ = font_weight;
    return *this;
}

// Задаёт текстовое содержимое объекта (отображается внутри тега text)
Text& Text::SetData(std::string data) {
    data_ = data;
    return *this;
}

void Text::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<text"sv;
    out << " x=\""sv << pos_.x
        << "\" y=\""sv << pos_.y << "\" "sv
        << "dx=\""sv << offset_.x
        << "\" dy=\""sv << offset_.y << "\" "sv
        << "font-size=\""sv << font_size_ << "\""sv;
    if (font_family_) {
        out << " font-family=\""sv << *font_family_ << "\""sv;
    }
    if (font_weight_) {
        out << " font-weight=\""sv << *font_weight_ << "\""sv;
    }
    this->PathProps::RenderAttrs(out);
    out << ">"sv;

    for (char c : data_) {
        switch (c) {
        case '\"':
            out << "&quot;"sv;
            break;
        case '\'':
            out << "&apos;"sv;
            break;
        case '<':
            out << "&lt;"sv;
            break;
        case '>':
            out << "&gt;"sv;
            break;
        case '&':
            out << "&amp;"sv;
            break;
        default:
            out << c;
            break;
        }
    }

    out << "</text>"sv;

}


// ---------- Document ----------------

void Document::AddPtr(std::unique_ptr<Object>&& obj_ptr) {
    objects_.emplace_back(std::move(obj_ptr));
}

void Document::Render(std::ostream& out) const {
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"sv << std::endl;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"sv << std::endl;
    for (const auto& obj : objects_) {
        obj->Render(RenderContext(out, 2, 2)); //2 2?
    }
    out << "</svg>"sv;
}

}  // namespace svg


// -------------Shapes-----------------------
namespace shapes {

namespace detail {
svg::Polyline CreateStar(svg::Point center, double outer_rad, double inner_rad, int num_rays) {
    using namespace svg;
    Polyline polyline;
    for (int i = 0; i <= num_rays; ++i) {
        double angle = 2 * M_PI * (i % num_rays) / num_rays;
        polyline.AddPoint({center.x + outer_rad * sin(angle), center.y - outer_rad * cos(angle)});
        if (i == num_rays) {
            break;
        }
        angle += M_PI / num_rays;
        polyline.AddPoint({center.x + inner_rad * sin(angle), center.y - inner_rad * cos(angle)});
    }
    return polyline;
}
} // namespace detail

const svg::Color STAR_FILL_COLOR { "red" };
const svg::Color STAR_STROKE_COLOR { "black" };
const svg::Color SNOWMAN_FILL_COLOR { "rgb(240,240,240)" };
const svg::Color SNOWMAN_STROKE_COLOR { "black" };

// ----------------Triangle------------------------------

Triangle::Triangle(svg::Point p1, svg::Point p2, svg::Point p3)
    : p1_(p1), p2_(p2), p3_(p3) {}

// Реализует метод Draw интерфейса svg::Drawable
void Triangle::Draw(svg::ObjectContainer& container) const {
    container.Add(svg::Polyline().AddPoint(p1_).AddPoint(p2_).AddPoint(p3_).AddPoint(p1_));
}

// ----------------Star------------------------------

Star::Star(svg::Point center, double outer_radius, double inner_radius, int num_rays)
    : center_(center), outer_radius_(outer_radius), inner_radius_(inner_radius), num_rays_(num_rays) {}

void Star::Draw(svg::ObjectContainer& container) const {
    container.Add(detail::CreateStar(center_, outer_radius_, inner_radius_, num_rays_).
                  SetFillColor(STAR_FILL_COLOR).SetStrokeColor(STAR_STROKE_COLOR));
}

// ----------------Snowman------------------------------

Snowman::Snowman(svg::Point center, double head_radius)
    : center_(center), head_radius_(head_radius) {}

void Snowman::Draw(svg::ObjectContainer& container) const {
    container.Add(svg::Circle().
                  SetCenter({ center_.x, center_.y + 5 * head_radius_ }).
                  SetRadius(2 * head_radius_).
                  SetFillColor(SNOWMAN_FILL_COLOR).SetStrokeColor(SNOWMAN_STROKE_COLOR));

    container.Add(svg::Circle().
                  SetCenter({ center_.x, center_.y + 2 * head_radius_ }).
                  SetRadius(1.5 * head_radius_).
                  SetFillColor(SNOWMAN_FILL_COLOR).SetStrokeColor(SNOWMAN_STROKE_COLOR));

    container.Add(svg::Circle().
                  SetCenter( { center_.x, center_.y }).
                  SetRadius(head_radius_).
                  SetFillColor(SNOWMAN_FILL_COLOR).SetStrokeColor(SNOWMAN_STROKE_COLOR));
}

} // namespace shapes
