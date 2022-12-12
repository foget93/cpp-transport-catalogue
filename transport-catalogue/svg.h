#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <deque>
#include <vector>
#include <optional>
#include <iostream>
#include <variant>


namespace svg {

struct Rgb {
    Rgb() = default;
    Rgb(unsigned int _red, unsigned int _green, unsigned int _blue)
        : red(_red), green(_green), blue(_blue) {
    }

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};

struct Rgba {
    Rgba() = default;
    Rgba(unsigned int _red, unsigned int _green, unsigned int _blue, double _opacity)
        : red(_red), green(_green), blue(_blue), opacity(_opacity) {
    }

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    double opacity = 1.0;
};

using Color = std::variant<std::monostate, std::string, Rgb, Rgba>;
inline const Color NoneColor = { };

//печатает svg::color в std::ostream
struct ColorPrintVisitor {
    std::ostream &out_;

    void operator()(std::monostate);
    void operator()(std::string &str);
    void operator()(Rgb color);
    void operator()(Rgba color);
};

enum class StrokeLineCap {
    BUTT,
    ROUND,
    SQUARE,
};

enum class StrokeLineJoin {
    ARCS,
    BEVEL,
    MITER,
    MITER_CLIP,
    ROUND,
};


/*
 * Наследование от этого класса разрешает выставить объекту свойства,
 * применимые к фигурам с контуром.
 *
 * Шаблонный параметр `Owner` должен быть равен типу, который наследует
 * этот класс (Curiously Recurring Template Pattern):
 *
 * class Circle final : public Object, public PathProps<Circle> {
 *
 * }
 *
 */
}// svg
std::ostream& operator<<(std::ostream &out, svg::StrokeLineCap);
std::ostream& operator<<(std::ostream &out, svg::StrokeLineJoin);
std::ostream& operator<<(std::ostream &out, svg::Color);

namespace  svg {

template <typename Owner>
class PathProps {
public:
    //цвет заполнения (атрибут fill)
    Owner& SetFillColor(Color color) {
        fill_color_ = std::move(color);
        return AsOwner();
    }

    //цвет контура (атрибут stroke)
    Owner& SetStrokeColor(Color color) {
        stroke_color_ = std::move(color);
        return AsOwner();
    }

    //толщина линий контура (атрибут stroke-width)
    Owner& SetStrokeWidth(double width) {
      stroke_width_ = width;
      return AsOwner();
    }

    //тип формы конца линии (атрибут stroke-linecap)
    Owner& SetStrokeLineCap(StrokeLineCap line_cap) {
      stroke_line_cap_ = line_cap;
      return AsOwner();
    }

    // тип формы соединения линии (атрибут stroke-linejoin)
    Owner& SetStrokeLineJoin(StrokeLineJoin line_join) {
      stroke_line_join_ = line_join;
      return AsOwner();
    }


protected:
    ~PathProps() = default;

    void RenderAttrs(std::ostream& out) const {
        using namespace std::literals;

        if (fill_color_) {
            out << " fill=\""sv << *fill_color_ << "\""sv;
        }
        if (stroke_color_) {
            out << " stroke=\""sv << *stroke_color_ << "\""sv;
        }
        if (stroke_width_) {
          out << " stroke-width=\""sv << *stroke_width_ << "\""sv;
        }
        if (stroke_line_cap_) {
          out << " stroke-linecap=\""sv;
          out << *stroke_line_cap_;
          out << "\""sv;
        }
        if (stroke_line_join_) {
          out << " stroke-linejoin=\""sv << *stroke_line_join_ << "\""sv;
        }
    }

private:
    Owner& AsOwner() {
        // static_cast безопасно преобразует *this к Owner&,
        // если класс Owner — наследник PathProps
        return static_cast<Owner&>(*this);
    }

    std::optional<Color> fill_color_;
    std::optional<Color> stroke_color_;
    std::optional<double> stroke_width_;
    std::optional<StrokeLineCap> stroke_line_cap_;
    std::optional<StrokeLineJoin> stroke_line_join_;
};

struct Point {
    Point() = default;
    Point(double x, double y)
        : x(x)
        , y(y) {
    }
    double x = 0;
    double y = 0;
};

/*
 * Вспомогательная структура, хранящая контекст для вывода SVG-документа с отступами.
 * Хранит ссылку на поток вывода, текущее значение и шаг отступа при выводе элемента
 */
struct RenderContext {
    RenderContext(std::ostream& out)
        : out(out) {
    }

    RenderContext(std::ostream& out, int indent_step, int indent = 0)
        : out(out)
        , indent_step(indent_step)
        , indent(indent) {
    }

    RenderContext Indented() const {
        return {out, indent_step, indent + indent_step};
    }

    void RenderIndent() const {
        for (int i = 0; i < indent; ++i) {
            out.put(' ');
        }
    }

    std::ostream& out;
    int indent_step = 0;
    int indent = 0;
};

/*
 * Абстрактный базовый класс Object служит для унифицированного хранения
 * конкретных тегов SVG-документа
 * Реализует паттерн "Шаблонный метод" для вывода содержимого тега
 */
class Object {
public:
    void Render(const RenderContext& context) const;

    virtual ~Object() = default;

private:
    virtual void RenderObject(const RenderContext& context) const = 0;
};

/*
 * Класс Circle моделирует элемент <circle> для отображения круга
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
 */
class Circle final : public Object, public PathProps<Circle> {
public:
    Circle& SetCenter(Point center);
    Circle& SetRadius(double radius);

private:
    void RenderObject(const RenderContext& context) const override;

    Point center_;
    double radius_ = 1.0;
};

/*
 * Класс Polyline моделирует элемент <polyline> для отображения ломаных линий
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polyline
 */
class Polyline final: public Object, public PathProps<Polyline> {
public:
    // Добавляет очередную вершину к ломаной линии
    Polyline& AddPoint(Point point);

private:
    void RenderObject(const RenderContext& context) const override;

    std::vector<Point> points_;
};

/*
 * Класс Text моделирует элемент <text> для отображения текста
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/text
 */
class Text final: public Object, public PathProps<Text> {
public:
    // Задаёт координаты опорной точки (атрибуты x и y)
    Text& SetPosition(Point pos);

    // Задаёт смещение относительно опорной точки (атрибуты dx, dy)
    Text& SetOffset(Point offset);

    // Задаёт размеры шрифта (атрибут font-size)
    Text& SetFontSize(uint32_t size);

    // Задаёт название шрифта (атрибут font-family)
    Text& SetFontFamily(std::string font_family);

    // Задаёт толщину шрифта (атрибут font-weight)
    Text& SetFontWeight(std::string font_weight);

    // Задаёт текстовое содержимое объекта (отображается внутри тега text)
    Text& SetData(std::string data);

private:
    void RenderObject(const RenderContext& context) const override;

    Point pos_ {};
    Point offset_ {};
    std::optional<std::string> font_family_;
    std::string data_;
    uint32_t font_size_ {1};
    std::optional<std::string> font_weight_;
};

/*
 * интерфейс(скорее абстрактный класс) для доступа к контейнеру svg-обьектов,
 * через него drawable-обьекты могут визуализировать себя добавляя в контейнер svg-примитивы
*/
class ObjectContainer {
public:
    /*
     Метод Add добавляет в svg-документ любой объект-наследник svg::Object.
     Пример использования:
     Document doc;
     doc.Add(Circle().SetCenter({20, 30}).SetRadius(15));
    */
    template<typename Obj>
    void Add(Obj obj) {
        AddPtr(std::make_unique<Obj>(std::move(obj)));
    }

    virtual void AddPtr(std::unique_ptr<Object>&& obj) = 0;

protected:
    ~ObjectContainer() = default;
};


class Document final : public ObjectContainer {
public:
    // Добавляет в svg-документ объект-наследник svg::Object
    void AddPtr(std::unique_ptr<Object>&& obj) override;

    // Выводит в ostream svg-представление документа
    void Render(std::ostream& out) const;

    // Прочие методы и данные, необходимые для реализации класса Document
private:
    std::deque<std::unique_ptr<Object>> objects_;
};

/*обьект который можно нарисовать с помощью ObjectContainer*/
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void Draw(ObjectContainer& container) const = 0;
};

}  // namespace svg


namespace shapes {

namespace detail {
svg::Polyline CreateStar(svg::Point center, double outer_rad, double inner_rad, int num_rays);
} // namespace detail

class Triangle final : public svg::Drawable {
public:
    Triangle(svg::Point p1, svg::Point p2, svg::Point p3);
    void Draw(svg::ObjectContainer& container) const override;

private:
    svg::Point p1_, p2_, p3_;
};

class Star final : public svg::Drawable {
public:
    Star(svg::Point center, double outer_radius, double inner_radius, int num_rays);

    void Draw(svg::ObjectContainer& container) const override;

private:
    svg::Point center_;
    double outer_radius_ = 0;
    double inner_radius_ = 0;
    int num_rays_ = 0;
};

class Snowman final : public svg::Drawable {
public:
    Snowman(svg::Point center, double head_radius);
    void Draw(svg::ObjectContainer& container) const override;

private:
    svg::Point center_;
    double head_radius_;
};

} // namespace shapes
/*
#include "svg.h"




//Класс Document должен реализовывать интерфейс svg::ObjectContainer. Это позволит создать композицию из произвольных Drawable-объектов и создать на их основе SVG-документ:
//Скопировать код
//CPP

template <typename DrawableIterator>
void DrawPicture(DrawableIterator begin, DrawableIterator end, svg::ObjectContainer& target) {
    for (auto it = begin; it != end; ++it) {
        (*it)->Draw(target);
    }
}

template <typename Container>
void DrawPicture(const Container& container, svg::ObjectContainer& target) {
    using namespace std;
    DrawPicture(begin(container), end(container), target);
}

void main_1() {
    using namespace svg;
    using namespace shapes;
    using namespace std;

    vector<unique_ptr<svg::Drawable>> picture;

    picture.emplace_back(make_unique<Triangle>(Point{100, 20}, Point{120, 50}, Point{80, 40}));
    //picture.emplace_back(make_unique<Triangle>(Point{200, 20}, Point{220, 50}, Point{180, 40}));
    // 5-лучевая звезда с центром {50, 20}, длиной лучей 10 и внутренним радиусом 4
    picture.emplace_back(make_unique<Star>(Point{50.0, 20.0}, 10.0, 4.0, 5));
    // Снеговик с "головой" радиусом 10, имеющей центр в точке {30, 20}
    picture.emplace_back(make_unique<Snowman>(Point{30, 20}, 10.0));

    svg::Document doc;
    // Так как документ реализует интерфейс ObjectContainer,
    // его можно передать в DrawPicture в качестве цели для рисования
    DrawPicture(picture, doc);

    // Выводим полученный документ в stdout
    doc.Render(cout);*/

    /*vector<unique_ptr<svg::Drawable>> picture;
    picture.emplace_back(make_unique<Triangle>(Point{100, 20}, Point{120, 50}, Point{80, 40}));
    picture.emplace_back(make_unique<Star>(Point{50.0, 20.0}, 10.0, 4.0, 5));
    picture.emplace_back(make_unique<Snowman>(Point{30, 20}, 10.0));

    svg::Document doc;
    DrawPicture(picture, doc);

    const Text base_text =  //
        Text()
            .SetFontFamily("Verdana"s)
            .SetFontSize(12)
            .SetPosition({10, 100})
            .SetData("Happy New Year!"s);
    doc.Add(Text{base_text}
                .SetStrokeColor("yellow"s)
                .SetFillColor("yellow"s)
                .SetStrokeLineJoin(StrokeLineJoin::ROUND)
                .SetStrokeLineCap(StrokeLineCap::ROUND)
                .SetStrokeWidth(3));
    doc.Add(Text{base_text}.SetFillColor("red"s));

    doc.Render(cout);

    Color none_color;
    cout << none_color << endl; // none

    Color purple{"purple"s};
    cout << purple << endl; // purple

    Color rgb = Rgb{100, 200, 255};
    cout << rgb << endl; // rgb(100,200,255)

    Color rgba = Rgba{100, 200, 255, 0.5};
    cout << rgba << endl; // rgba(100,200,255,0.5)

    Circle c;
    c.SetRadius(3.5).SetCenter({1.0, 2.0});
    c.SetFillColor(rgba);
    c.SetStrokeColor(purple);

    Document doc;
    doc.Add(std::move(c));
    doc.Render(cout);
}

uint8_t Lerp(uint8_t from, uint8_t to, double t) {
    return static_cast<uint8_t>(std::round((to - from) * t + from));
}

int main() {
    using namespace svg;
    using namespace std;

    const uint8_t start_r = 0;
    const uint8_t end_r = 20;
    const uint8_t start_g = 255;
    const uint8_t end_g = 20;
    const uint8_t start_b = 30;
    const uint8_t end_b = 150;

    const int num_circles = 10;
    Document doc;
    for (int i = 0; i < num_circles; ++i) {
        const double t = double(i) / (num_circles - 1);

        const string r = to_string(Lerp(start_r, end_r, t));
        const string g = to_string(Lerp(start_g, end_g, t));
        const string b = to_string(Lerp(start_b, end_b, t));

        string fill_color = "rgb("s + r + ","s + g + ","s + b + ")"s;
        doc.Add(Circle()
                    .SetFillColor(fill_color)
                    .SetStrokeColor("black"s)
                    .SetCenter({i * 20.0 + 40, 40.0})
                    .SetRadius(15));
    }
    doc.Render(cout);
}

*/
