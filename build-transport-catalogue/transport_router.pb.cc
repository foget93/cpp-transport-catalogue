// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: transport_router.proto

#include "transport_router.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace transport_catalogue_serialize {
PROTOBUF_CONSTEXPR RoutingSettings::RoutingSettings(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.bus_velocity_kmh_)*/0
  , /*decltype(_impl_.bus_wait_time_min_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct RoutingSettingsDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RoutingSettingsDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RoutingSettingsDefaultTypeInternal() {}
  union {
    RoutingSettings _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RoutingSettingsDefaultTypeInternal _RoutingSettings_default_instance_;
PROTOBUF_CONSTEXPR TransportRouter::TransportRouter(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.bus_routes_)*/{}
  , /*decltype(_impl_.settings_)*/nullptr
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct TransportRouterDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TransportRouterDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~TransportRouterDefaultTypeInternal() {}
  union {
    TransportRouter _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TransportRouterDefaultTypeInternal _TransportRouter_default_instance_;
}  // namespace transport_catalogue_serialize
static ::_pb::Metadata file_level_metadata_transport_5frouter_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_transport_5frouter_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_transport_5frouter_2eproto = nullptr;

const uint32_t TableStruct_transport_5frouter_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::RoutingSettings, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::RoutingSettings, _impl_.bus_wait_time_min_),
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::RoutingSettings, _impl_.bus_velocity_kmh_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::TransportRouter, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::TransportRouter, _impl_.settings_),
  PROTOBUF_FIELD_OFFSET(::transport_catalogue_serialize::TransportRouter, _impl_.bus_routes_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::transport_catalogue_serialize::RoutingSettings)},
  { 8, -1, -1, sizeof(::transport_catalogue_serialize::TransportRouter)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::transport_catalogue_serialize::_RoutingSettings_default_instance_._instance,
  &::transport_catalogue_serialize::_TransportRouter_default_instance_._instance,
};

const char descriptor_table_protodef_transport_5frouter_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026transport_router.proto\022\035transport_cata"
  "logue_serialize\032\013graph.proto\"F\n\017RoutingS"
  "ettings\022\031\n\021bus_wait_time_min\030\001 \001(\r\022\030\n\020bu"
  "s_velocity_kmh\030\002 \001(\001\"\220\001\n\017TransportRouter"
  "\022@\n\010settings\030\001 \001(\0132..transport_catalogue"
  "_serialize.RoutingSettings\022;\n\nbus_routes"
  "\030\002 \003(\0132\'.transport_catalogue_serialize.B"
  "usRouteb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_transport_5frouter_2eproto_deps[1] = {
  &::descriptor_table_graph_2eproto,
};
static ::_pbi::once_flag descriptor_table_transport_5frouter_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_transport_5frouter_2eproto = {
    false, false, 295, descriptor_table_protodef_transport_5frouter_2eproto,
    "transport_router.proto",
    &descriptor_table_transport_5frouter_2eproto_once, descriptor_table_transport_5frouter_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_transport_5frouter_2eproto::offsets,
    file_level_metadata_transport_5frouter_2eproto, file_level_enum_descriptors_transport_5frouter_2eproto,
    file_level_service_descriptors_transport_5frouter_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_transport_5frouter_2eproto_getter() {
  return &descriptor_table_transport_5frouter_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_transport_5frouter_2eproto(&descriptor_table_transport_5frouter_2eproto);
namespace transport_catalogue_serialize {

// ===================================================================

class RoutingSettings::_Internal {
 public:
};

RoutingSettings::RoutingSettings(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:transport_catalogue_serialize.RoutingSettings)
}
RoutingSettings::RoutingSettings(const RoutingSettings& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  RoutingSettings* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.bus_velocity_kmh_){}
    , decltype(_impl_.bus_wait_time_min_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.bus_velocity_kmh_, &from._impl_.bus_velocity_kmh_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.bus_wait_time_min_) -
    reinterpret_cast<char*>(&_impl_.bus_velocity_kmh_)) + sizeof(_impl_.bus_wait_time_min_));
  // @@protoc_insertion_point(copy_constructor:transport_catalogue_serialize.RoutingSettings)
}

inline void RoutingSettings::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.bus_velocity_kmh_){0}
    , decltype(_impl_.bus_wait_time_min_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

RoutingSettings::~RoutingSettings() {
  // @@protoc_insertion_point(destructor:transport_catalogue_serialize.RoutingSettings)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RoutingSettings::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void RoutingSettings::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RoutingSettings::Clear() {
// @@protoc_insertion_point(message_clear_start:transport_catalogue_serialize.RoutingSettings)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.bus_velocity_kmh_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.bus_wait_time_min_) -
      reinterpret_cast<char*>(&_impl_.bus_velocity_kmh_)) + sizeof(_impl_.bus_wait_time_min_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RoutingSettings::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 bus_wait_time_min = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.bus_wait_time_min_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // double bus_velocity_kmh = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 17)) {
          _impl_.bus_velocity_kmh_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* RoutingSettings::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:transport_catalogue_serialize.RoutingSettings)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 bus_wait_time_min = 1;
  if (this->_internal_bus_wait_time_min() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(1, this->_internal_bus_wait_time_min(), target);
  }

  // double bus_velocity_kmh = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_bus_velocity_kmh = this->_internal_bus_velocity_kmh();
  uint64_t raw_bus_velocity_kmh;
  memcpy(&raw_bus_velocity_kmh, &tmp_bus_velocity_kmh, sizeof(tmp_bus_velocity_kmh));
  if (raw_bus_velocity_kmh != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(2, this->_internal_bus_velocity_kmh(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:transport_catalogue_serialize.RoutingSettings)
  return target;
}

size_t RoutingSettings::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:transport_catalogue_serialize.RoutingSettings)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double bus_velocity_kmh = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_bus_velocity_kmh = this->_internal_bus_velocity_kmh();
  uint64_t raw_bus_velocity_kmh;
  memcpy(&raw_bus_velocity_kmh, &tmp_bus_velocity_kmh, sizeof(tmp_bus_velocity_kmh));
  if (raw_bus_velocity_kmh != 0) {
    total_size += 1 + 8;
  }

  // uint32 bus_wait_time_min = 1;
  if (this->_internal_bus_wait_time_min() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_bus_wait_time_min());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RoutingSettings::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    RoutingSettings::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RoutingSettings::GetClassData() const { return &_class_data_; }


void RoutingSettings::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<RoutingSettings*>(&to_msg);
  auto& from = static_cast<const RoutingSettings&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:transport_catalogue_serialize.RoutingSettings)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_bus_velocity_kmh = from._internal_bus_velocity_kmh();
  uint64_t raw_bus_velocity_kmh;
  memcpy(&raw_bus_velocity_kmh, &tmp_bus_velocity_kmh, sizeof(tmp_bus_velocity_kmh));
  if (raw_bus_velocity_kmh != 0) {
    _this->_internal_set_bus_velocity_kmh(from._internal_bus_velocity_kmh());
  }
  if (from._internal_bus_wait_time_min() != 0) {
    _this->_internal_set_bus_wait_time_min(from._internal_bus_wait_time_min());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RoutingSettings::CopyFrom(const RoutingSettings& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:transport_catalogue_serialize.RoutingSettings)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoutingSettings::IsInitialized() const {
  return true;
}

void RoutingSettings::InternalSwap(RoutingSettings* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RoutingSettings, _impl_.bus_wait_time_min_)
      + sizeof(RoutingSettings::_impl_.bus_wait_time_min_)
      - PROTOBUF_FIELD_OFFSET(RoutingSettings, _impl_.bus_velocity_kmh_)>(
          reinterpret_cast<char*>(&_impl_.bus_velocity_kmh_),
          reinterpret_cast<char*>(&other->_impl_.bus_velocity_kmh_));
}

::PROTOBUF_NAMESPACE_ID::Metadata RoutingSettings::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_transport_5frouter_2eproto_getter, &descriptor_table_transport_5frouter_2eproto_once,
      file_level_metadata_transport_5frouter_2eproto[0]);
}

// ===================================================================

class TransportRouter::_Internal {
 public:
  static const ::transport_catalogue_serialize::RoutingSettings& settings(const TransportRouter* msg);
};

const ::transport_catalogue_serialize::RoutingSettings&
TransportRouter::_Internal::settings(const TransportRouter* msg) {
  return *msg->_impl_.settings_;
}
void TransportRouter::clear_bus_routes() {
  _impl_.bus_routes_.Clear();
}
TransportRouter::TransportRouter(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:transport_catalogue_serialize.TransportRouter)
}
TransportRouter::TransportRouter(const TransportRouter& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  TransportRouter* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.bus_routes_){from._impl_.bus_routes_}
    , decltype(_impl_.settings_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_settings()) {
    _this->_impl_.settings_ = new ::transport_catalogue_serialize::RoutingSettings(*from._impl_.settings_);
  }
  // @@protoc_insertion_point(copy_constructor:transport_catalogue_serialize.TransportRouter)
}

inline void TransportRouter::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.bus_routes_){arena}
    , decltype(_impl_.settings_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

TransportRouter::~TransportRouter() {
  // @@protoc_insertion_point(destructor:transport_catalogue_serialize.TransportRouter)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void TransportRouter::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.bus_routes_.~RepeatedPtrField();
  if (this != internal_default_instance()) delete _impl_.settings_;
}

void TransportRouter::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void TransportRouter::Clear() {
// @@protoc_insertion_point(message_clear_start:transport_catalogue_serialize.TransportRouter)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.bus_routes_.Clear();
  if (GetArenaForAllocation() == nullptr && _impl_.settings_ != nullptr) {
    delete _impl_.settings_;
  }
  _impl_.settings_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* TransportRouter::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .transport_catalogue_serialize.RoutingSettings settings = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_settings(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .transport_catalogue_serialize.BusRoute bus_routes = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_bus_routes(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* TransportRouter::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:transport_catalogue_serialize.TransportRouter)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .transport_catalogue_serialize.RoutingSettings settings = 1;
  if (this->_internal_has_settings()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::settings(this),
        _Internal::settings(this).GetCachedSize(), target, stream);
  }

  // repeated .transport_catalogue_serialize.BusRoute bus_routes = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_bus_routes_size()); i < n; i++) {
    const auto& repfield = this->_internal_bus_routes(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:transport_catalogue_serialize.TransportRouter)
  return target;
}

size_t TransportRouter::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:transport_catalogue_serialize.TransportRouter)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .transport_catalogue_serialize.BusRoute bus_routes = 2;
  total_size += 1UL * this->_internal_bus_routes_size();
  for (const auto& msg : this->_impl_.bus_routes_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // .transport_catalogue_serialize.RoutingSettings settings = 1;
  if (this->_internal_has_settings()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.settings_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData TransportRouter::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    TransportRouter::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*TransportRouter::GetClassData() const { return &_class_data_; }


void TransportRouter::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<TransportRouter*>(&to_msg);
  auto& from = static_cast<const TransportRouter&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:transport_catalogue_serialize.TransportRouter)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.bus_routes_.MergeFrom(from._impl_.bus_routes_);
  if (from._internal_has_settings()) {
    _this->_internal_mutable_settings()->::transport_catalogue_serialize::RoutingSettings::MergeFrom(
        from._internal_settings());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void TransportRouter::CopyFrom(const TransportRouter& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:transport_catalogue_serialize.TransportRouter)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TransportRouter::IsInitialized() const {
  return true;
}

void TransportRouter::InternalSwap(TransportRouter* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.bus_routes_.InternalSwap(&other->_impl_.bus_routes_);
  swap(_impl_.settings_, other->_impl_.settings_);
}

::PROTOBUF_NAMESPACE_ID::Metadata TransportRouter::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_transport_5frouter_2eproto_getter, &descriptor_table_transport_5frouter_2eproto_once,
      file_level_metadata_transport_5frouter_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace transport_catalogue_serialize
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::transport_catalogue_serialize::RoutingSettings*
Arena::CreateMaybeMessage< ::transport_catalogue_serialize::RoutingSettings >(Arena* arena) {
  return Arena::CreateMessageInternal< ::transport_catalogue_serialize::RoutingSettings >(arena);
}
template<> PROTOBUF_NOINLINE ::transport_catalogue_serialize::TransportRouter*
Arena::CreateMaybeMessage< ::transport_catalogue_serialize::TransportRouter >(Arena* arena) {
  return Arena::CreateMessageInternal< ::transport_catalogue_serialize::TransportRouter >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
