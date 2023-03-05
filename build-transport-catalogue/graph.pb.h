// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: graph.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_graph_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_graph_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021011 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_graph_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_graph_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_graph_2eproto;
namespace transport_catalogue_serialize {
class BusRoute;
struct BusRouteDefaultTypeInternal;
extern BusRouteDefaultTypeInternal _BusRoute_default_instance_;
}  // namespace transport_catalogue_serialize
PROTOBUF_NAMESPACE_OPEN
template<> ::transport_catalogue_serialize::BusRoute* Arena::CreateMaybeMessage<::transport_catalogue_serialize::BusRoute>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace transport_catalogue_serialize {

// ===================================================================

class BusRoute final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:transport_catalogue_serialize.BusRoute) */ {
 public:
  inline BusRoute() : BusRoute(nullptr) {}
  ~BusRoute() override;
  explicit PROTOBUF_CONSTEXPR BusRoute(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  BusRoute(const BusRoute& from);
  BusRoute(BusRoute&& from) noexcept
    : BusRoute() {
    *this = ::std::move(from);
  }

  inline BusRoute& operator=(const BusRoute& from) {
    CopyFrom(from);
    return *this;
  }
  inline BusRoute& operator=(BusRoute&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const BusRoute& default_instance() {
    return *internal_default_instance();
  }
  static inline const BusRoute* internal_default_instance() {
    return reinterpret_cast<const BusRoute*>(
               &_BusRoute_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(BusRoute& a, BusRoute& b) {
    a.Swap(&b);
  }
  inline void Swap(BusRoute* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BusRoute* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  BusRoute* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<BusRoute>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const BusRoute& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const BusRoute& from) {
    BusRoute::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(BusRoute* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "transport_catalogue_serialize.BusRoute";
  }
  protected:
  explicit BusRoute(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFromStopIdFieldNumber = 1,
    kToStopIdFieldNumber = 2,
    kBusIdFieldNumber = 3,
    kSpanCountFieldNumber = 4,
    kWeightFieldNumber = 5,
  };
  // uint32 from_stop_id = 1;
  void clear_from_stop_id();
  uint32_t from_stop_id() const;
  void set_from_stop_id(uint32_t value);
  private:
  uint32_t _internal_from_stop_id() const;
  void _internal_set_from_stop_id(uint32_t value);
  public:

  // uint32 to_stop_id = 2;
  void clear_to_stop_id();
  uint32_t to_stop_id() const;
  void set_to_stop_id(uint32_t value);
  private:
  uint32_t _internal_to_stop_id() const;
  void _internal_set_to_stop_id(uint32_t value);
  public:

  // uint32 bus_id = 3;
  void clear_bus_id();
  uint32_t bus_id() const;
  void set_bus_id(uint32_t value);
  private:
  uint32_t _internal_bus_id() const;
  void _internal_set_bus_id(uint32_t value);
  public:

  // uint32 span_count = 4;
  void clear_span_count();
  uint32_t span_count() const;
  void set_span_count(uint32_t value);
  private:
  uint32_t _internal_span_count() const;
  void _internal_set_span_count(uint32_t value);
  public:

  // double weight = 5;
  void clear_weight();
  double weight() const;
  void set_weight(double value);
  private:
  double _internal_weight() const;
  void _internal_set_weight(double value);
  public:

  // @@protoc_insertion_point(class_scope:transport_catalogue_serialize.BusRoute)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    uint32_t from_stop_id_;
    uint32_t to_stop_id_;
    uint32_t bus_id_;
    uint32_t span_count_;
    double weight_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_graph_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// BusRoute

// uint32 from_stop_id = 1;
inline void BusRoute::clear_from_stop_id() {
  _impl_.from_stop_id_ = 0u;
}
inline uint32_t BusRoute::_internal_from_stop_id() const {
  return _impl_.from_stop_id_;
}
inline uint32_t BusRoute::from_stop_id() const {
  // @@protoc_insertion_point(field_get:transport_catalogue_serialize.BusRoute.from_stop_id)
  return _internal_from_stop_id();
}
inline void BusRoute::_internal_set_from_stop_id(uint32_t value) {
  
  _impl_.from_stop_id_ = value;
}
inline void BusRoute::set_from_stop_id(uint32_t value) {
  _internal_set_from_stop_id(value);
  // @@protoc_insertion_point(field_set:transport_catalogue_serialize.BusRoute.from_stop_id)
}

// uint32 to_stop_id = 2;
inline void BusRoute::clear_to_stop_id() {
  _impl_.to_stop_id_ = 0u;
}
inline uint32_t BusRoute::_internal_to_stop_id() const {
  return _impl_.to_stop_id_;
}
inline uint32_t BusRoute::to_stop_id() const {
  // @@protoc_insertion_point(field_get:transport_catalogue_serialize.BusRoute.to_stop_id)
  return _internal_to_stop_id();
}
inline void BusRoute::_internal_set_to_stop_id(uint32_t value) {
  
  _impl_.to_stop_id_ = value;
}
inline void BusRoute::set_to_stop_id(uint32_t value) {
  _internal_set_to_stop_id(value);
  // @@protoc_insertion_point(field_set:transport_catalogue_serialize.BusRoute.to_stop_id)
}

// uint32 bus_id = 3;
inline void BusRoute::clear_bus_id() {
  _impl_.bus_id_ = 0u;
}
inline uint32_t BusRoute::_internal_bus_id() const {
  return _impl_.bus_id_;
}
inline uint32_t BusRoute::bus_id() const {
  // @@protoc_insertion_point(field_get:transport_catalogue_serialize.BusRoute.bus_id)
  return _internal_bus_id();
}
inline void BusRoute::_internal_set_bus_id(uint32_t value) {
  
  _impl_.bus_id_ = value;
}
inline void BusRoute::set_bus_id(uint32_t value) {
  _internal_set_bus_id(value);
  // @@protoc_insertion_point(field_set:transport_catalogue_serialize.BusRoute.bus_id)
}

// uint32 span_count = 4;
inline void BusRoute::clear_span_count() {
  _impl_.span_count_ = 0u;
}
inline uint32_t BusRoute::_internal_span_count() const {
  return _impl_.span_count_;
}
inline uint32_t BusRoute::span_count() const {
  // @@protoc_insertion_point(field_get:transport_catalogue_serialize.BusRoute.span_count)
  return _internal_span_count();
}
inline void BusRoute::_internal_set_span_count(uint32_t value) {
  
  _impl_.span_count_ = value;
}
inline void BusRoute::set_span_count(uint32_t value) {
  _internal_set_span_count(value);
  // @@protoc_insertion_point(field_set:transport_catalogue_serialize.BusRoute.span_count)
}

// double weight = 5;
inline void BusRoute::clear_weight() {
  _impl_.weight_ = 0;
}
inline double BusRoute::_internal_weight() const {
  return _impl_.weight_;
}
inline double BusRoute::weight() const {
  // @@protoc_insertion_point(field_get:transport_catalogue_serialize.BusRoute.weight)
  return _internal_weight();
}
inline void BusRoute::_internal_set_weight(double value) {
  
  _impl_.weight_ = value;
}
inline void BusRoute::set_weight(double value) {
  _internal_set_weight(value);
  // @@protoc_insertion_point(field_set:transport_catalogue_serialize.BusRoute.weight)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace transport_catalogue_serialize

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_graph_2eproto
