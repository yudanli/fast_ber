#pragma once

#include "fast_ber/compiler/CppGeneration.hpp"

#include "absl/memory/memory.h"
#include "absl/types/optional.h"
#include "absl/types/variant.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static const std::unordered_set<std::string> reserved_keywords = {"alignas",
                                                                  "alignof",
                                                                  "and",
                                                                  "and_eq",
                                                                  "asm",
                                                                  "atomic_cancel",
                                                                  "atomic_commit",
                                                                  "atomic_noexcept",
                                                                  "auto",
                                                                  "bitand",
                                                                  "bitor",
                                                                  "bool",
                                                                  "break",
                                                                  "case",
                                                                  "catch",
                                                                  "char",
                                                                  "char8_t",
                                                                  "char16_t",
                                                                  "char32_t",
                                                                  "class",
                                                                  "compl",
                                                                  "concept",
                                                                  "const",
                                                                  "consteval",
                                                                  "constexpr",
                                                                  "const_cast",
                                                                  "continue",
                                                                  "co_await",
                                                                  "co_return",
                                                                  "co_yield",
                                                                  "decltype",
                                                                  "default",
                                                                  "delete",
                                                                  "do",
                                                                  "double",
                                                                  "dynamic_cast",
                                                                  "else",
                                                                  "enum",
                                                                  "explicit",
                                                                  "export",
                                                                  "extern",
                                                                  "false",
                                                                  "float",
                                                                  "for",
                                                                  "friend",
                                                                  "goto",
                                                                  "if",
                                                                  "import",
                                                                  "inline",
                                                                  "int",
                                                                  "long",
                                                                  "module",
                                                                  "mutable",
                                                                  "namespace",
                                                                  "new",
                                                                  "noexcept",
                                                                  "not",
                                                                  "not_eq",
                                                                  "nullptr",
                                                                  "operator",
                                                                  "or",
                                                                  "or_eq",
                                                                  "private",
                                                                  "protected",
                                                                  "public",
                                                                  "reflexpr",
                                                                  "register",
                                                                  "reinterpret_cast",
                                                                  "requires",
                                                                  "return",
                                                                  "short",
                                                                  "signed",
                                                                  "sizeof",
                                                                  "static",
                                                                  "static_assert",
                                                                  "static_cast",
                                                                  "struct",
                                                                  "switch",
                                                                  "synchronized",
                                                                  "template",
                                                                  "this",
                                                                  "thread_local",
                                                                  "throw",
                                                                  "true",
                                                                  "try",
                                                                  "typedef",
                                                                  "typeid",
                                                                  "typename",
                                                                  "union",
                                                                  "unsigned",
                                                                  "using",
                                                                  "virtual",
                                                                  "void",
                                                                  "volatile",
                                                                  "wchar_t",
                                                                  "while",
                                                                  "xor",
                                                                  "xor_eq"};

// Switch asn '-' for C++ '_'
// Rename any names which are reserved in C++
std::string santize_name(const std::string& name)
{
    auto copy = name;
    std::replace(copy.begin(), copy.end(), '-', '_');

    if (reserved_keywords.count(copy) > 0)
    {
        return copy + "_";
    }
    return copy;
}

enum class TaggingMode
{
    explicit_,
    implicit,
    automatic
};

enum class Class
{
    universal,
    application,
    context_specific,
    private_,
};

struct ComponentType;
struct TaggedType;
using ComponentTypeList = std::vector<ComponentType>;

struct NamedType;
struct NamedNumber
{
    std::string name;
    int64_t     number;
};
struct EnumerationValue
{
    std::string             name;
    absl::optional<int64_t> value;
};

struct AnyType
{
};
struct BitStringType
{
};
struct BooleanType
{
};
struct CharacterStringType
{
};
struct ChoiceType;
struct DateType
{
};
struct DateTimeType
{
};
struct DurationType
{
};
struct EmbeddedPDVType
{
};
struct EnumeratedType
{
    std::vector<EnumerationValue> enum_values;
    bool                          accept_anything;
};
struct ExternalType
{
};
struct GeneralizedTimeType
{
};
struct InstanceOfType
{
};
struct IntegerType
{
    std::vector<NamedNumber> named_numbers;
};
struct IRIType
{
};
struct NullType
{
};
struct ObjectClassFieldType
{
};
struct ObjectDescriptorType
{
};
struct ObjectIdentifierType
{
};
struct OctetStringType
{
};
struct RealType
{
};
struct RelativeIRIType
{
};
struct RelativeOIDType
{
};
struct SequenceType
{
    ComponentTypeList components;
};
struct SequenceOfType;
struct SetType
{
    ComponentTypeList components;
};
struct SetOfType;

// unique ptr used to avoid circular reference on stack
struct PrefixedType
{
    PrefixedType() = default;
    PrefixedType(const TaggedType& type) : tagged_type(absl::make_unique<TaggedType>(type)) {}
    PrefixedType(const PrefixedType& rhs)
    {
        if (rhs.tagged_type)
        {
            tagged_type = absl::make_unique<TaggedType>(*rhs.tagged_type);
        }
    }
    PrefixedType& operator=(const PrefixedType& rhs)
    {
        if (rhs.tagged_type)
        {
            tagged_type = absl::make_unique<TaggedType>(*rhs.tagged_type);
        }
        return *this;
    }
    std::unique_ptr<TaggedType> tagged_type;
};
struct TimeType
{
};
struct TimeOfDayType
{
};
struct UTCTimeType
{
};
struct DefinedType;

using BuiltinType =
    absl::variant<AnyType, BitStringType, BooleanType, CharacterStringType, ChoiceType, DateType, DateTimeType,
                  DurationType, EmbeddedPDVType, EnumeratedType, ExternalType, GeneralizedTimeType, InstanceOfType,
                  IntegerType, IRIType, NullType, ObjectClassFieldType, ObjectDescriptorType, ObjectIdentifierType,
                  OctetStringType, RealType, RelativeIRIType, RelativeOIDType, SequenceType, SequenceOfType, SetType,
                  SetOfType, PrefixedType, TimeType, TimeOfDayType, UTCTimeType>;
using Type = absl::variant<BuiltinType, DefinedType>;

struct DefinedType
{
    std::string       name;
    std::vector<Type> parameters;
};
struct SequenceOfType
{
    // Shared pointers used to prevent circular references
    bool                       has_name;
    std::shared_ptr<NamedType> named_type;
    std::shared_ptr<Type>      type;
};
struct SetOfType
{
    // Shared pointers used to prevent circular references
    bool                       has_name;
    std::shared_ptr<NamedType> named_type;
    std::shared_ptr<Type>      type;
};

struct ChoiceType
{
    std::vector<NamedType> choices;
};

struct DefinedValue
{
    std::string reference;
};

struct BitStringValue
{
    std::string value;
};

struct HexStringValue
{
    std::string value;
};

struct CharStringValue
{
    std::string value;
};

struct Value
{
    absl::optional<DefinedValue> defined_value;
    absl::variant<std::vector<Value>, int64_t, std::string, NamedNumber, BitStringValue, HexStringValue,
                  CharStringValue>
        value_selection;
};

struct NamedType
{
    std::string name;
    Type        type;
};

struct NamedValue
{
    std::string name;
    Value       type;
};

struct ComponentType
{
    NamedType             named_type;
    bool                  is_optional;
    absl::optional<Value> value;
};

struct Tag
{
    Class class_;
    int   tag_number;
};

struct TaggedType
{
    Tag         tag;
    TaggingMode tagging_mode;
    Type        type;
};

struct TypeAssignment
{
    Type type;
};

struct ValueAssignment
{
    Type  type;
    Value value;
};

struct ObjectClassAssignment
{
};

struct ObjectSetAssignment
{
};

struct Assignment
{
    std::string                                                                                name;
    absl::variant<TypeAssignment, ValueAssignment, ObjectClassAssignment, ObjectSetAssignment> specific;
    std::vector<std::string>                                                                   depends_on;
    std::set<std::string>                                                                      parameters;
};

struct Import
{
    std::string              module_reference;
    std::vector<std::string> imports;
};

struct Export
{
};

struct Module
{
    std::string             module_reference;
    TaggingMode             tagging_default;
    std::vector<Export>     exports;
    std::vector<Import>     imports;
    std::vector<Assignment> assignments;
};

struct Asn1Tree
{
    std::vector<Module> modules;
};

std::string to_string(Class class_)
{
    switch (class_)
    {
    case Class::universal:
        return "universal";
    case Class::application:
        return "application";
    case Class::context_specific:
        return "context_specific";
    case Class::private_:
        return "private_";
    default:
        return "";
    }
}

struct TaggingInfo
{
    std::string tag;
    bool        is_default_tagged;
};

struct ObjectIdComponentValue
{
    absl::optional<std::string> name;
    absl::optional<int64_t>     value;
};

struct ObjectIdComponents
{
    ObjectIdComponents(const Value& value)
    {
        if (!absl::holds_alternative<std::vector<Value>>(value.value_selection))
        {
            throw std::runtime_error("Failed to interpret value as object identifier");
        }
        const std::vector<Value>& value_list = absl::get<std::vector<Value>>(value.value_selection);
        components.reserve(value_list.size());
        for (const Value& component : value_list)
        {
            if (component.defined_value)
            {
                const std::string& name = component.defined_value->reference;
                components.push_back(ObjectIdComponentValue{name, absl::nullopt});
            }
            else if (absl::holds_alternative<std::string>(component.value_selection))
            {
                const std::string& name = absl::get<std::string>(component.value_selection);
                components.push_back(ObjectIdComponentValue{name, absl::nullopt});
            }
            else if (absl::holds_alternative<int64_t>(component.value_selection))
            {
                const int64_t& number = absl::get<int64_t>(component.value_selection);
                components.push_back(ObjectIdComponentValue{absl::nullopt, number});
            }
            else if (absl::holds_alternative<NamedNumber>(component.value_selection))
            {
                const NamedNumber& named_number = absl::get<NamedNumber>(component.value_selection);
                components.push_back(ObjectIdComponentValue{named_number.name, named_number.number});
            }
            else
            {
                throw std::runtime_error("Failed to interpret value as object identifier");
            }
        }
    }
    std::vector<ObjectIdComponentValue> components;
};

std::string to_string(const AnyType&);
std::string to_string(const BitStringType&);
std::string to_string(const BooleanType&);
std::string to_string(const CharacterStringType&);
std::string to_string(const ChoiceType&);
std::string to_string(const DateType&);
std::string to_string(const DateTimeType&);
std::string to_string(const DurationType&);
std::string to_string(const EmbeddedPDVType&);
std::string to_string(const EnumeratedType&);
std::string to_string(const ExternalType&);
std::string to_string(const GeneralizedTimeType& type);
std::string to_string(const InstanceOfType&);
std::string to_string(const IntegerType&);
std::string to_string(const IRIType&);
std::string to_string(const NullType&);
std::string to_string(const ObjectClassFieldType&);
std::string to_string(const ObjectDescriptorType&);
std::string to_string(const ObjectIdentifierType&);
std::string to_string(const OctetStringType&);
std::string to_string(const RealType&);
std::string to_string(const RelativeIRIType&);
std::string to_string(const RelativeOIDType&);
std::string to_string(const SequenceType&);
std::string to_string(const SequenceOfType&);
std::string to_string(const SetType&);
std::string to_string(const SetOfType&);
std::string to_string(const PrefixedType&);
std::string to_string(const TimeType&);
std::string to_string(const TimeOfDayType&);
std::string to_string(const UTCTimeType& type);
std::string to_string(const DefinedType&);
std::string to_string(const BuiltinType& type);
std::string to_string(const Type& type);
std::string fully_tagged_type(const Type& type, TaggingMode tagging_mode);

bool is_set(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) && absl::holds_alternative<SetType>(absl::get<BuiltinType>(type));
}

bool is_sequence(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<SequenceType>(absl::get<BuiltinType>(type));
}

bool is_set_of(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<SetOfType>(absl::get<BuiltinType>(type));
}

bool is_sequence_of(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<SequenceOfType>(absl::get<BuiltinType>(type));
}

bool is_enumerated(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<EnumeratedType>(absl::get<BuiltinType>(type));
}

bool is_choice(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<ChoiceType>(absl::get<BuiltinType>(type));
}

bool is_prefixed(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<PrefixedType>(absl::get<BuiltinType>(type));
}

bool is_integer(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<IntegerType>(absl::get<BuiltinType>(type));
}

bool is_oid(const Type& type)
{
    return absl::holds_alternative<BuiltinType>(type) &&
           absl::holds_alternative<ObjectIdentifierType>(absl::get<BuiltinType>(type));
}

bool is_defined(const Type& type) { return absl::holds_alternative<DefinedType>(type); }

int unnamed_definition_reference_num = 0;

std::string to_string(const AnyType&) { return "Any"; }
std::string to_string(const BitStringType&) { return "BitString"; }
std::string to_string(const BooleanType&) { return "Boolean"; }
std::string to_string(const CharacterStringType&) { return "CharacterString"; }
std::string to_string(const ChoiceType& choice)
{
    bool        is_first = true;
    std::string res      = "Choice<";
    for (const auto& named_type : choice.choices)
    {
        if (!is_first)
            res += ", ";

        if (is_sequence(named_type.type))
        {
            res += "UnnamedSequence" + std::to_string(unnamed_definition_reference_num++);
        }
        else if (is_set(named_type.type))
        {
            res += "UnnamedSet" + std::to_string(unnamed_definition_reference_num++);
        }
        else if (is_enumerated(named_type.type))
        {
            return "UnnamedEnum" + std::to_string(unnamed_definition_reference_num++);
        }
        else
        {
            res += fully_tagged_type(named_type.type, TaggingMode::implicit);
        }

        is_first = false;
    }

    res += ">";
    return res;
}
std::string to_string(const DateType&) { return "Date"; }
std::string to_string(const DateTimeType&) { return "DateTime"; }
std::string to_string(const DurationType&) { return "Duration"; }
std::string to_string(const EmbeddedPDVType&) { return "EmbeddedPDV"; }
std::string to_string(const EnumeratedType& enumerated)
{
    std::string res = " {\n";
    for (const EnumerationValue& enum_value : enumerated.enum_values)
    {
        res += "    " + enum_value.name;
        if (enum_value.value)
        {
            res += " = " + std::to_string(*enum_value.value);
        }
        res += ",\n";
    }
    res += "};\n\n";

    return res;
}
std::string to_string(const ExternalType&) { return "External"; }
std::string to_string(const GeneralizedTimeType&) { return "GeneralizedTime"; }
std::string to_string(const InstanceOfType&) { return "InstanceOf"; }
std::string to_string(const IntegerType&) { return "Integer"; }
std::string to_string(const IRIType&) { return "IRI"; }
std::string to_string(const NullType&) { return "Null"; }
std::string to_string(const ObjectClassFieldType&) { return "ObjectClassField"; }
std::string to_string(const ObjectDescriptorType&) { return "ObjectDescriptor"; }
std::string to_string(const ObjectIdentifierType&) { return "ObjectIdentifier"; }
std::string to_string(const OctetStringType&) { return "OctetString"; }
std::string to_string(const RealType&) { return "Real"; }
std::string to_string(const RelativeIRIType&) { return "RelativeIRI"; }
std::string to_string(const RelativeOIDType&) { return "RelativeOID"; }
std::string make_type_optional(const std::string& type) { return "Optional<" + type + ">"; }
std::string to_string(const SequenceType& sequence)
{
    std::string res = " {\n";

    for (const ComponentType& component : sequence.components)
    {
        std::string component_type = to_string(component.named_type.type);
        if (is_enumerated(component.named_type.type))
        {
            component_type = "UnnamedEnum" + std::to_string(unnamed_definition_reference_num++);
        }

        if (is_set(component.named_type.type) || is_sequence(component.named_type.type))
        {
            res += "struct " + component.named_type.name + "_type " + component_type;
            res += "    " + component.named_type.name + "_type " + component.named_type.name + ";\n";
        }
        else
        {
            if (component.is_optional)
            {
                component_type = make_type_optional(component_type);
            }
            res += "    " + component_type + " " + component.named_type.name + ";\n";
        }
    }
    res += "};\n";

    return res;
}
std::string to_string(const SequenceOfType& sequence)
{
    const Type& type = sequence.has_name ? sequence.named_type->type : *sequence.type;

    if (is_sequence(type))
    {
        if (sequence.has_name)
        {
            return "SequenceOf<" + sequence.named_type->name + ">";
        }
        return "SequenceOf<UnnamedSequence" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else if (is_set(type))
    {
        if (sequence.has_name)
        {
            return "SequenceOf<" + sequence.named_type->name + ">";
        }
        return "SequenceOf<UnnamedSet" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else if (is_enumerated(type))
    {
        if (sequence.has_name)
        {
            return "SequenceOf<" + sequence.named_type->name + ">";
        }
        return "SequenceOf<UnnamedEnum" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else
    {
        return "SequenceOf<" + to_string(type) + ">";
    }
}
std::string to_string(const SetType& set)
{
    std::string res = " {\n";

    for (const ComponentType& component : set.components)
    {
        std::string component_type = to_string(component.named_type.type);
        if (is_enumerated(component.named_type.type))
        {
            component_type = "UnnamedEnum" + std::to_string(unnamed_definition_reference_num++);
        }

        if (is_set(component.named_type.type) || is_sequence(component.named_type.type))
        {
            res += "    struct " + component.named_type.name + "_type " + component_type;
            res += component.named_type.name + "_type " + component.named_type.name + ";\n";
        }
        else
        {
            if (component.is_optional)
            {
                component_type = make_type_optional(component_type);
            }
            res += "    " + component_type + " " + component.named_type.name + ";\n";
        }
    }
    res += "};\n";

    return res;
}
std::string to_string(const SetOfType& set)
{
    const Type& type = set.has_name ? set.named_type->type : *set.type;

    if (is_sequence(type))
    {
        if (set.has_name)
        {
            return "SequenceOf<" + set.named_type->name + ">";
        }
        return "SequenceOf<UnnamedSequence" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else if (is_set(type))
    {
        if (set.has_name)
        {
            return "SequenceOf<" + set.named_type->name + ">";
        }
        return "SequenceOf<UnnamedSet" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else if (is_enumerated(type))
    {
        if (set.has_name)
        {
            return "SequenceOf<" + set.named_type->name + ">";
        }
        return "SequenceOf<UnnamedEnum" + std::to_string(unnamed_definition_reference_num++) + ">";
    }
    else
    {
        return "SequenceOf<" + to_string(type) + ">";
    }
}
std::string to_string(const PrefixedType& prefixed_type)
{
    if (is_sequence(prefixed_type.tagged_type->type))
    {
        return "UnnamedSequence" + std::to_string(unnamed_definition_reference_num++);
    }
    else if (is_set(prefixed_type.tagged_type->type))
    {
        return "UnnamedSet" + std::to_string(unnamed_definition_reference_num++);
    }
    else if (is_enumerated(prefixed_type.tagged_type->type))
    {
        return "UnnamedEnum" + std::to_string(unnamed_definition_reference_num++);
    }
    return to_string(prefixed_type.tagged_type->type);
}
std::string to_string(const TimeType&) { return "Time"; }
std::string to_string(const TimeOfDayType&) { return "TimeOfDay"; }
std::string to_string(const UTCTimeType&) { return "UTCTime"; }

std::string to_string(const DefinedType& type)
{
    if (!type.parameters.empty())
    {
        std::set<std::string> parameter_types;
        for (const Type& paramter : type.parameters)
        {
            parameter_types.insert(to_string(paramter));
        }
        return type.name + create_template_arguments(parameter_types);
    }
    return type.name;
}

struct ToStringHelper
{
    template <typename T>
    std::string operator()(const T& t)
    {
        return to_string(t);
    }
};

static ToStringHelper string_helper;

std::string to_string(const BuiltinType& type) { return absl::visit(string_helper, type); }
std::string to_string(const Type& type) { return absl::visit(string_helper, type); }

struct Context;
