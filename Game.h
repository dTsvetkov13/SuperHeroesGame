#pragma once

#include "Vector.hpp";
#include "MyString.h";
#include "Player.h"
#include "Admin.h"
#include "SharedPtr.hpp";
#include "GameMenu.h";
#include "RequestReturnModel.hpp"
#include "Market.h";
#include "AttackResult.h"
#include "MarketSaleResult.h"

class Game
{
private:
    const uint32_t MINIMUM_HEROES_COUNT = 3;

    struct GameConfig
    {
        double playerMoneyPerTurn;
        double moneyOnLose;
        double moneyOnDraw;
        double startingMoney;

        GameConfig() : GameConfig(100, 100, 100, 100) {}

        GameConfig(double pMoneyPerTurn, double moneyLose, double moneyDraw, double startMoney)
            : playerMoneyPerTurn(pMoneyPerTurn),
            moneyOnLose(moneyLose),
            moneyOnDraw(moneyDraw),
            startingMoney(startMoney) {}
    } _config;

    SharedPtr<User> _loggedUser;
    Vector<SharedPtr<Player>> _players;
    Vector<SharedPtr<Admin>> _admins;
    Vector<SharedPtr<SuperHero>> _graveyard;
    Market _market;

    //SharedPtr<Vector<SharedPtr<User>>> _players;
    //SharedPtr<Vector<SharedPtr<User>>> _admins;

    bool isNewGame = false;
    bool isFirstPlayerToLog = true;


    Game();

    void loadGame();
    void init();

    bool isUserLogged() const;
    bool isAdminLogged() const;

    //TODO: check this; make sure to be non-const
    Vector<Player> getRanking() const; //const
    RequestReturnModel<Vector<Admin>> getAdmins() const; //const
    RequestReturnModel<Vector<Player>> getPlayers()  const; //const

    bool addAdmin(const Admin&);
    bool addPlayer(const Player&);

    AttackResult loggedUserAttack(const MyString& otherName, const MyString& currUserHeroName,
        const MyString& otherUserHeroName);

    bool signIn(const MyString&, const MyString&, UserRole role);
    void logOut();

    void deleteUser(const MyString& name);

    void loadGameFromFile();

    void checkForTurnPaying();
    uint8_t getPlayerMostLogsCount() const;
    MarketSaleResult buySuperHero(const MyString&);

    double getLoggedPlayerBalance() const;
    void changeLoggedUserSuperHeroAttackMode(const MyString&, HeroAttackMode);

    template<typename P>
    Vector<P> getVector(const Vector<SharedPtr<P>>& v) const;

    bool isThereSuchUser(const MyString& name, UserRole role) const;
public:
    static Game& getInstance();
    void play();

    inline GameConfig getConfig() const { return _config; }

    ~Game();

    friend class GameMenu;
};

template<typename T>
Vector<T> Game::getVector(const Vector<SharedPtr<T>>& v) const
{
    Vector<T> result;

    for (int i = 0; i < v.getSize(); i++)
    {
        result.pushBack(*v[i]);
    }

    return result;
}