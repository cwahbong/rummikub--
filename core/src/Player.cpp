#include "Player.h"

#include "model/Hand.h"

using std::string;

namespace rummikub {

struct Player::Member {
  string id;
  s_ptr<Agent> sp_agent;
  s_ptr<Hand> sp_hand;
};

Player::Player(const string& id, const s_ptr<Agent>& sp_agent)
  : _{new Member{id, sp_agent, make_s<Hand>()}}
{/* Empty. */}

Player::~Player()
{/* Empty. */}

string
Player::getId() const
{
  return _->id;
}

s_ptr<Agent>
Player::getAgent() const
{
  return _->sp_agent;
}

s_ptr<Hand>
Player::getHand() const
{
  return _->sp_hand;
}

} // namespace rummikub

