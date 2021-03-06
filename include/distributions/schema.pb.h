// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: distributions/schema.proto

#ifndef PROTOBUF_distributions_2fschema_2eproto__INCLUDED
#define PROTOBUF_distributions_2fschema_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace distributions {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_distributions_2fschema_2eproto();
void protobuf_AssignDesc_distributions_2fschema_2eproto();
void protobuf_ShutdownFile_distributions_2fschema_2eproto();

class Row;

// ===================================================================

class Row : public ::google::protobuf::Message {
 public:
  Row();
  virtual ~Row();
  
  Row(const Row& from);
  
  inline Row& operator=(const Row& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Row& default_instance();
  
  void Swap(Row* other);
  
  // implements Message ----------------------------------------------
  
  Row* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Row& from);
  void MergeFrom(const Row& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  
  // repeated bool booleans = 2;
  inline int booleans_size() const;
  inline void clear_booleans();
  static const int kBooleansFieldNumber = 2;
  inline bool booleans(int index) const;
  inline void set_booleans(int index, bool value);
  inline void add_booleans(bool value);
  inline const ::google::protobuf::RepeatedField< bool >&
      booleans() const;
  inline ::google::protobuf::RepeatedField< bool >*
      mutable_booleans();
  
  // repeated uint32 categoricals = 3;
  inline int categoricals_size() const;
  inline void clear_categoricals();
  static const int kCategoricalsFieldNumber = 3;
  inline ::google::protobuf::uint32 categoricals(int index) const;
  inline void set_categoricals(int index, ::google::protobuf::uint32 value);
  inline void add_categoricals(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      categoricals() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_categoricals();
  
  // repeated float reals = 4;
  inline int reals_size() const;
  inline void clear_reals();
  static const int kRealsFieldNumber = 4;
  inline float reals(int index) const;
  inline void set_reals(int index, float value);
  inline void add_reals(float value);
  inline const ::google::protobuf::RepeatedField< float >&
      reals() const;
  inline ::google::protobuf::RepeatedField< float >*
      mutable_reals();
  
  // @@protoc_insertion_point(class_scope:distributions.Row)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* id_;
  ::google::protobuf::RepeatedField< bool > booleans_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > categoricals_;
  ::google::protobuf::RepeatedField< float > reals_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_distributions_2fschema_2eproto();
  friend void protobuf_AssignDesc_distributions_2fschema_2eproto();
  friend void protobuf_ShutdownFile_distributions_2fschema_2eproto();
  
  void InitAsDefaultInstance();
  static Row* default_instance_;
};
// ===================================================================


// ===================================================================

// Row

// optional string id = 1;
inline bool Row::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Row::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Row::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Row::clear_id() {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& Row::id() const {
  return *id_;
}
inline void Row::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void Row::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void Row::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Row::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  return id_;
}
inline ::std::string* Row::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// repeated bool booleans = 2;
inline int Row::booleans_size() const {
  return booleans_.size();
}
inline void Row::clear_booleans() {
  booleans_.Clear();
}
inline bool Row::booleans(int index) const {
  return booleans_.Get(index);
}
inline void Row::set_booleans(int index, bool value) {
  booleans_.Set(index, value);
}
inline void Row::add_booleans(bool value) {
  booleans_.Add(value);
}
inline const ::google::protobuf::RepeatedField< bool >&
Row::booleans() const {
  return booleans_;
}
inline ::google::protobuf::RepeatedField< bool >*
Row::mutable_booleans() {
  return &booleans_;
}

// repeated uint32 categoricals = 3;
inline int Row::categoricals_size() const {
  return categoricals_.size();
}
inline void Row::clear_categoricals() {
  categoricals_.Clear();
}
inline ::google::protobuf::uint32 Row::categoricals(int index) const {
  return categoricals_.Get(index);
}
inline void Row::set_categoricals(int index, ::google::protobuf::uint32 value) {
  categoricals_.Set(index, value);
}
inline void Row::add_categoricals(::google::protobuf::uint32 value) {
  categoricals_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Row::categoricals() const {
  return categoricals_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Row::mutable_categoricals() {
  return &categoricals_;
}

// repeated float reals = 4;
inline int Row::reals_size() const {
  return reals_.size();
}
inline void Row::clear_reals() {
  reals_.Clear();
}
inline float Row::reals(int index) const {
  return reals_.Get(index);
}
inline void Row::set_reals(int index, float value) {
  reals_.Set(index, value);
}
inline void Row::add_reals(float value) {
  reals_.Add(value);
}
inline const ::google::protobuf::RepeatedField< float >&
Row::reals() const {
  return reals_;
}
inline ::google::protobuf::RepeatedField< float >*
Row::mutable_reals() {
  return &reals_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace distributions

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_distributions_2fschema_2eproto__INCLUDED
