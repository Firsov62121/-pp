#include "helpful_objs.h"
#include <cassert>

namespace Civilization{

int get_rand(int min, int max) //srand was used before
{ 
    if(max < min)
        std::swap(max, min);
    return min + rand() % (max - min + 1);
}

Pos::Pos(size_t x, size_t y) noexcept : x(x), y(y) {}
Pos::Pos(const Pos& other) noexcept : x(other.x), y(other.y) {}

Pos& Pos::operator=(const Pos& other) noexcept
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Pos::operator==(const Pos& other) const noexcept
{
    return x == other.x && y == other.y;
}

bool Pos::operator!=(const Pos& other) const noexcept
{
    return !(*this == other);
}

bool Pos::operator<(const Pos& other) const noexcept
{
    return x < other.x || (x == other.x && y < other.y);
}

bool Pos::operator>(const Pos& other) const noexcept
{
    return *this != other && !(*this < other);
}

uint FieldObject::getPlayerId() const noexcept
{
    return playerId;
}

FieldType FieldObject::getType() const noexcept
{
    return type;
}

bool FieldObject::operator==(const FieldObject& other) const noexcept
{
    return playerId == other.playerId && pos == other.pos && 
        type == other.type && power == other.power;
}

bool FieldObject::operator!=(const FieldObject& other) const noexcept
{
    return !(*this == other);
}

bool FieldObject::operator<(const FieldObject& other) const noexcept
{
    return playerId < other.playerId || static_cast<int>(type) < 
        static_cast<int>(other.type) || pos < other.pos || 
        power < other.power;
}

bool FieldObject::operator>(const FieldObject& other) const noexcept
{
    return other < (*this);
}

FieldObject::FieldObject(uint playerId, FieldType ft, uint power, const Pos& pos) noexcept : 
    playerId(playerId), type(ft), power(power), pos(pos){}

FieldObject& FieldObject::operator=(const FieldObject& other) noexcept {
    if(this != &other)
    {
        playerId = other.playerId;
        type = other.type;
        pos = other.pos;
        power = other.power;
    }
    return *this;
}

static inline CollapseRes cityOrSquadsCollapse(FieldObject& fo1, FieldObject& fo2)
{
    if(fo2.getPlayerId() == fo1.getPlayerId())
    {
        if(fo1.getType() == FieldType::CityCell)
        {
            fo1.power += fo2.power;
            fo2.power = 0;
            return CollapseRes::SECOND;
        }
        fo2.power += fo1.power;
        fo1.power = 0;
        return CollapseRes::FIRST;
    }
    if(fo1.power > fo2.power)
    {
        fo1.power -= fo2.power;
        fo2.power = 0;
        return CollapseRes::SECOND;
    }
    if(fo1.power < fo2.power)
    {
        fo2.power -= fo1.power;
        fo1.power = 0;
        return CollapseRes::FIRST;
    }
    fo2.power = fo1.power = 0;
    return CollapseRes::BOTH;
}

static inline CollapseRes cityCollapse(FieldObject& city, FieldObject& other)
{
    switch (other.getType())
    {
    case FieldType::Squad:
        return cityOrSquadsCollapse(city, other);
    default:
        assert(false && "This FieldType couldn't move!");
    }
    return CollapseRes::NONE;
}

static inline CollapseRes squadCollapse(FieldObject& squad, FieldObject& other)
{
    switch (other.getType())
    {
    case FieldType::BadPlace:
        squad.power = 0;
        return CollapseRes::FIRST;
    case FieldType::CityCell:
    case FieldType::Squad:
        return cityOrSquadsCollapse(squad, other);
    case FieldType::Free:
        return CollapseRes::SECOND;
    default:
        // assert false
        assert(false && "Unknown FiledType");
    }
    return CollapseRes::NONE;
}

CollapseRes collapse(FieldObject& first, FieldObject& second)
{
    switch (first.getType())
    {
    case FieldType::CityCell:
        return cityCollapse(first, second);
    case FieldType::BadPlace:
        second.power = 0;
        return CollapseRes::SECOND;
    case FieldType::Free:
        first.power = 0;
        return CollapseRes::FIRST;
    case FieldType::Squad:
        return squadCollapse(first, second);
    default:
        // Unknown FiledType
        assert(false && "Unknown FiledType");
    }

    return CollapseRes::NONE;
}

uint Player::countOfObjs() const
{
    return objects.size();
}

uint Player::getId() const noexcept
{
    return id;
}

void Player::addObject(const std::shared_ptr<FieldObject>& object)
{
    objects.insert(std::move(object));
}

void Player::removeObject(std::shared_ptr<FieldObject> const& object)
{
    objects.erase(object);
}

Player::Player(uint id) : id(id) {}

Field::Field(size_t n, size_t m) : n(n), m(m), data(n * m, std::make_shared<FieldObject>()) {}

Field::Field(const Pos& p) : Field(p.x, p.y) {}

std::shared_ptr<FieldObject>& Field::get(const Pos& p)
{
    assert(p.x >= 0 && p.y >=0 && p.x < n && p.y < m && "PosOutOfFieldIndexes");
    return data[p.x * m + p.y];
}

const std::shared_ptr<const FieldObject> Field::get(const Pos& p) const
{
    assert(p.x >= 0 && p.y >=0 && p.x < n && p.y < m && "PosOutOfFieldIndexes");
    return data[p.x * m + p.y];
}

void Field::set(const Pos& p, const std::shared_ptr<FieldObject>& value)
{
    assert(p.x >= 0 && p.y >=0 && p.x < n && p.y < m && "PosOutOfFieldIndexes");
    data[p.x * m + p.y] = value;
}

}