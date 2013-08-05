#include "Player.h"

#include "model/Hand.h"

using std::make_shared;
using std::string;

namespace rummikub {

struct Player::Member {
  string id;
  cs_ptr<Agent> sp_agent;
  s_ptr<Hand> sp_hand;
};

Player::Player(const string& id, const cs_ptr<Agent>& sp_agent)
  : _{new Member{id, sp_agent, make_shared<Hand>()}}
{/* Empty. */}

Player::~Player()
{/* Empty. */}

string
Player::getId() const
{
  return _->id;
}

cs_ptr<Agent>
Player::getAgent() const
{
  return _->sp_agent;
}

s_ptr<Hand>
Player::getHand()
{
  return _->sp_hand;
}

} // namespace rummikub

