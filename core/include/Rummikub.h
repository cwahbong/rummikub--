#ifndef RUMMIKUB_CORE__RUMMIKUB_H
#define RUMMIKUB_CORE__RUMMIKUB_H

#include "CoreFwd.h"

#include "Player.h"
#include "Table.h"
#include "TileManager.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace rummikub {
namespace core {

enum RummiMessage {
  SET_INSERT,
  SET_REMOVE,
  SET_DELETE,
};

template <>
struct MessageTraits<Rummikub> {
  using Type = Rummikub;
  using MessageType = RummiMessage;
};

template <>
struct CallbackTraits<Rummikub> {
  using MessageType = RummiMessage;
  template <MessageType> struct CallbackFunction;
};

template <>
struct CallbackTraits<Rummikub>::CallbackFunction<SET_INSERT> {
  using Type = std::function<void(const Tile&)>;
};

template <>
struct CallbackTraits<Rummikub>::CallbackFunction<SET_REMOVE> {
  using Type = std::function<void(const Tile&)>;
};

template<>
struct CallbackTraits<Rummikub>::CallbackFunction<SET_DELETE> {
  using Type = std::function<void()>;
};

class Rummikub {
public:
  typedef std::function<void(const std::shared_ptr<const Player>)> TurnCallback;
  typedef std::function<void()> GameCallback;

private:
  std::shared_ptr<Notifier<Rummikub>> m_sp_notifier;
  std::shared_ptr<TileManager> m_sp_tileManager;
  std::shared_ptr<Table> m_sp_table;
  std::vector<std::shared_ptr<Player>> m_sp_players;
  std::vector<TurnCallback> m_turnStartCallbacks;
  std::vector<TurnCallback> m_turnEndCallbacks;
  std::vector<GameCallback> m_gameEndCallbacks;

  void turnStart(const std::shared_ptr<const Player>&);
  void turnEnd(const std::shared_ptr<const Player>&);
  void gameEnd();

public:
  template <typename InputIterator>
  Rummikub(InputIterator first, InputIterator end)
    : m_sp_tileManager{TileManager::newShuffledTiles()},
      m_sp_table{Table::newTable()},
      m_sp_players{},
      m_turnStartCallbacks{},
      m_turnEndCallbacks{},
      m_gameEndCallbacks{}
  {
    std::for_each(first, end, [this] (const std::shared_ptr<Agent>& agent) mutable {
      const auto& sp_player = Player::newPlayer();
      sp_player->setAgent(agent);
      m_sp_players.push_back(sp_player);
    });
  }


  std::vector<std::weak_ptr<Player>> getPlayers();
  std::shared_ptr<Notifier<Rummikub>> getNotifier() const;
  void addTurnStartCallback(TurnCallback);
  void addTurnEndCallback(TurnCallback);
  void addGameEndCallback(GameCallback);
  void startGame();
};

} // namespace core
} // namespace rmmikub

#endif // RUMMIKUB_CORE__RUMMIKUB_H

