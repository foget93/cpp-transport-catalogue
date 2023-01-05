#pragma once

#include <stack>
#include <optional>

#include "json.h"

namespace json {
    //class KeyValueContext;
    class KeyItemContext;
    class DictItemContext;
    class ArrayItemContext;

    class Builder {
    public:
        Builder() = default;
        Node Build() const;
        DictItemContext/*Builder*/ StartDict();
        Builder& EndDict();
        ArrayItemContext/*Builder*/ StartArray();
        Builder& EndArray();
        KeyItemContext/*Builder*/ Key(const std::string & key);
        Builder& Value(const Node& value, bool is_start = false);

    private:
        Node root_ = nullptr;
        std::stack<Node*> nodes_stack_;

        bool is_root_empty_ = true;
        std::optional<std::string> key_;
    };

// ================================================================

    class Context {
    public:
        explicit Context(Builder& builder);

    protected:
        Builder& builder_;
    };

    class KeyValueContext final : public Context {
    public:
        explicit KeyValueContext(Builder& builder);
        KeyItemContext Key(const std::string& key);
        Builder& EndDict();
    };

    class KeyItemContext final : public Context {
    public:
        explicit KeyItemContext(Builder& builder);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        KeyValueContext Value(const Node& value, bool is_start = false);
    };

    class DictItemContext final : public Context {
    public:
        explicit DictItemContext(Builder& builder);
        KeyItemContext Key(const std::string& key) const;
        Builder& EndDict() const;
    };

    class ArrayItemContext final : public Context {
    public:
        explicit ArrayItemContext(Builder& builder);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        Builder& EndArray();
        ArrayItemContext Value(const Node& value, bool is_start = false);
    };

} // namespace json
