// Copyright (c) 2022 Papa Libasse Sow.
// https://github.com/Nandite/bazaar_traits
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef TESTS_CLASSES_HPP
#define TESTS_CLASSES_HPP

#include <algorithm>

struct Tp {};
struct StructTypeWithEnumMember { enum EnumMember { }; };
enum EnumType {};
enum class EnumClassWithSignedUnderlyingType : int {};
enum class EnumClassWithUnsignedUnderlyingType : unsigned int {};
struct EmptyStructType {};
class EmptyClassType {};
enum class EnumClassType {};
union UnionTypeWithClassMember { class [[maybe_unused]] UnionClassMemberType {}; };
typedef union {
    int a;
    float b;
} UnionType;
struct StructWithUnionMemberType {
    UnionType d;
};
enum class EnumWithUnderlyingChar : char {};
enum class EnumWithUnderlyingShort : short {};
enum class EnumWithUnderlyingInt : int {};
enum class EnumWithUnderlyingLong : long {};
enum class EnumWithUnderlyingLongLong : long long {};
enum class EnumWithUnderlyingUChar : unsigned char {};
enum class EnumWithUnderlyingUShort : unsigned short {};
enum class EnumWithUnderlyingUInt : unsigned int {};
enum class EnumWithUnderlyingULong : unsigned long {};
enum class EnumWithUnderlyingULongLong : unsigned long long {};
class Constructible {
public:
    explicit Constructible(int){};
    explicit Constructible(float){};
    Constructible(int, std::size_t){};
    explicit Constructible(EnumClassType){};
    explicit Constructible(EmptyClassType){};
    explicit Constructible(EmptyClassType, Tp, UnionTypeWithClassMember){};
};
class ImplicitConstructibleClass {};
class NoThrowConstructible {
public:
    explicit NoThrowConstructible (int) noexcept {};
    explicit NoThrowConstructible(float) noexcept {};
    NoThrowConstructible(int, std::size_t) noexcept {};
    explicit NoThrowConstructible(EnumClassType) noexcept {};
    explicit NoThrowConstructible(EmptyClassType) noexcept {};
    explicit NoThrowConstructible(EmptyClassType, Tp, UnionTypeWithClassMember) noexcept {};
};
class ExplicitDefaultConstructors {
public:
    ExplicitDefaultConstructors() = default;
    ExplicitDefaultConstructors(const ExplicitDefaultConstructors &) = default;
    ExplicitDefaultConstructors(ExplicitDefaultConstructors&&) = default;
};
class DeletedConstructors {
public:
    DeletedConstructors() = delete;
    DeletedConstructors(const DeletedConstructors &) = delete;
    DeletedConstructors(DeletedConstructors&&) = delete;
};
class ExplicitNoThrowConstructors {
public:
    ExplicitNoThrowConstructors() noexcept = default;
    ExplicitNoThrowConstructors(const ExplicitNoThrowConstructors &) noexcept = default;
    ExplicitNoThrowConstructors(ExplicitNoThrowConstructors&&) noexcept = default;
};
class ExplicitThrowConstructors {
public:
    ExplicitThrowConstructors() noexcept(false) = default;
    ExplicitThrowConstructors(const ExplicitThrowConstructors &) noexcept(false) = default;
    ExplicitThrowConstructors(ExplicitThrowConstructors&&) noexcept(false) = default;
};

class ExplicitCopyConstructibleClass {
public:
    ExplicitCopyConstructibleClass(const ExplicitCopyConstructibleClass &)= default;
};
class NonCopyConstructibleClass{
public:
    NonCopyConstructibleClass(const NonCopyConstructibleClass &)= delete;
};
class NonTriviallyCopyableClass_1{
public:
    NonTriviallyCopyableClass_1(const NonTriviallyCopyableClass_1 &) {
        int a, b;
        std::swap(a,b);
    };
};
class NonTriviallyCopyableClass_2{
public:
    NonTriviallyCopyableClass_2(NonTriviallyCopyableClass_2 &&)  noexcept {
        int a, b;
        std::swap(a,b);
    };
};
class NonTriviallyCopyableClass_3{
public:
    NonTriviallyCopyableClass_3& operator=(const NonTriviallyCopyableClass_3&) {
        int a, b;
        std::swap(a,b);
        return *this;
    };
};
class NonTriviallyCopyableClass_4{
public:
    NonTriviallyCopyableClass_4& operator=(NonTriviallyCopyableClass_4&&) {
        int a, b;
        std::swap(a,b);
        return *this;
    };
};
struct ImplicitCopyConstructibleStruct {};
struct ExplicitCopyConstructibleStruct {
    ExplicitCopyConstructibleStruct(const ExplicitCopyConstructibleStruct &)= default;
};
struct NonCopyConstructibleStruct{
    NonCopyConstructibleStruct(const NonCopyConstructibleStruct &)= delete;
};
class ImplicitMoveConstructibleClass {};
class ExplicitMoveConstructibleClass {
public:
    ExplicitMoveConstructibleClass(ExplicitMoveConstructibleClass &&)= default;
};
class NonMoveConstructibleClass{
public:
    NonMoveConstructibleClass(NonMoveConstructibleClass &&)= delete;
};
struct ImplicitMoveConstructibleStruct {};
struct ExplicitMoveConstructibleStruct {
    ExplicitMoveConstructibleStruct(ExplicitMoveConstructibleStruct &&)= default;
};
struct NonMoveConstructibleStruct{
    NonMoveConstructibleStruct(NonMoveConstructibleStruct &&)= delete;
};
class AssignableFromIntClass {
public:
    AssignableFromIntClass& operator=(const int&){return *this;};
};
class NonAssignableClass {
public:
    NonAssignableClass& operator=(const NonAssignableClass &) = delete;
    NonAssignableClass& operator=(NonAssignableClass &&) = delete;
    NonAssignableClass& operator=(const int&) = delete;
};
class NonTriviallyAssignable {
public:
    NonTriviallyAssignable& operator=(const NonTriviallyAssignable&){
        int a, b;
        std::swap(a,b);
        return *this;
    };
    NonTriviallyAssignable& operator=(NonTriviallyAssignable&&) noexcept {
        int a, b;
        std::swap(a,b);
        return *this;
    };
};
class TriviallyAssignable {
public:
    TriviallyAssignable& operator=(const TriviallyAssignable&) = default;
    TriviallyAssignable& operator=(TriviallyAssignable&&)= default;
};
class NoThrowAssignable {
public:
    NoThrowAssignable& operator=(const NoThrowAssignable&) noexcept = default;
    NoThrowAssignable& operator=(NoThrowAssignable&&) noexcept = default;
};
class ThrowAssignable {
public:
    ThrowAssignable& operator=(const ThrowAssignable&) noexcept(false) = default;
    ThrowAssignable& operator=(ThrowAssignable&&) noexcept(false) = default;
};
class NoThrowAssignableAndConstructible {
public:
    NoThrowAssignableAndConstructible(NoThrowAssignableAndConstructible&&) noexcept = default;
    NoThrowAssignableAndConstructible& operator=(const NoThrowAssignableAndConstructible&) noexcept = default;
    NoThrowAssignableAndConstructible& operator=(NoThrowAssignableAndConstructible&&) noexcept = default;
};
class DefaultDestructibleClass {
public:
    ~DefaultDestructibleClass() = default;
};
class NonDestructibleClass {
public:
    ~NonDestructibleClass() = delete;
};
class ThrowDestructibleClass {
public:
    ~ThrowDestructibleClass() noexcept(false) = default;
};
class NoThrowDestructibleClass {
public:
    ~NoThrowDestructibleClass() noexcept = default;
};
class NonTriviallyDestructibleClass {
public:
    ~NonTriviallyDestructibleClass() = delete;
};
class VirtualClass
{
public:
    [[maybe_unused]] virtual void fuzz() {};
};
class VirtualPureClass
{
    [[maybe_unused]] virtual void fuzz() = 0;
};
class DerivedFromVirtualClass : public VirtualClass{};
class DerivedFromVirtualPureClass : public VirtualPureClass{};
class VirtualDestructorClass {
    virtual ~VirtualDestructorClass() = default;
};
class ClassWithDifferentAccessControl
{
public:
    int publicMember{};
private:
    int privateMember{};
};
class ClassWithReferenceMemberType
{
    explicit ClassWithReferenceMemberType(int & reference) : referenceMember(reference){};
private:
    int & referenceMember;
};
struct Q {};
struct S : Q { };
struct T : Q { };
struct HasTwoBaseClassSubObjects : S, T { };
struct PrivateInheritedBaseClass : private Q{};
struct ProtectedInheritedBaseClass : protected Q{};
class finalClass final{};
class finalStruct final{};
class PrivateMemberClass{
private:
    int a;
};
class ProtectedMemberClass{
private:
    int a;
};
class DefaultMemberInitializationClass
{
    int a{};
    int b{};
};
struct NonUniqueObjectRepresentationStruct
{
    char c;
    float f;
    short st;
    int i;
};

struct UniqueObjectRepresentationStruct
{
    int a;
    int b;
};

#endif //TESTS_CLASSES_HPP
