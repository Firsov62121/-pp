#pragma once
#include <string>
#include <set>
#include <vector>
#include <memory>

namespace Civilization{

struct Pos
{
    size_t x;
    size_t y;
    Pos(size_t x, size_t y) noexcept;
    Pos(const Pos& other) noexcept;
    Pos& operator=(const Pos& other) noexcept;
    bool operator==(const Pos& other) const noexcept;
    bool operator!=(const Pos& other) const noexcept;
    bool operator<(const Pos& other) const noexcept;
    bool operator>(const Pos& other) const noexcept;
};

enum class CollapseRes {FIRST, SECOND, BOTH, NONE}; //who was destroyed
enum class FieldType {CityCell, BadPlace, Free, Squad};

class FieldObject
{
    uint playerId;
    FieldType type;

public:
    uint power;
    Pos pos;

    uint getPlayerId() const noexcept;
    FieldType getType() const noexcept;
    bool operator==(const FieldObject& other) const noexcept;
    bool operator!=(const FieldObject& other) const noexcept;
    bool operator<(const FieldObject& other) const noexcept;
    bool operator>(const FieldObject& other) const noexcept;

    FieldObject(uint playerId = 0, FieldType ft = FieldType::Free, uint power = 0, const Pos& pos = Pos(0, 0)) noexcept;
    FieldObject& operator=(const FieldObject& other) noexcept;
};

struct Player
{
    uint id;
    std::set<std::shared_ptr<FieldObject>> objects;
public:
    uint getId() const noexcept;
    void addObject(const std::shared_ptr<FieldObject>& object);
    void removeObject(const std::shared_ptr<FieldObject>& object);
    uint countOfObjs() const;

    Player(uint id);
};

class Field
{
    size_t n, m;
    std::vector<std::shared_ptr<FieldObject>> data {}; // В C++ почти всегда всможно обойтись без укатзателей на указатели, Scott Maers
public:
    Field(size_t n, size_t m);
    Field(const Pos& p);
    std::shared_ptr<FieldObject>& get(const Pos& p);
    const std::shared_ptr<const FieldObject> get(const Pos& p) const;
    void set(const Pos& p, const std::shared_ptr<FieldObject>& value);
};

int get_rand(int min = -100, int max = 100);
CollapseRes collapse(FieldObject& first, FieldObject& second);
}