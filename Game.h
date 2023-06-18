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

class Game
{
private:
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
    SharedPtr<Vector<Player>> _players;
    SharedPtr<Vector<Admin>> _admins;
    SharedPtr<Vector<SuperHero>> _graveyard;
    Market _market;

    //SharedPtr<Vector<SharedPtr<User>>> _players;
    //SharedPtr<Vector<SharedPtr<User>>> _admins;

    bool isNewGame = false;


    Game();

    void loadGame();

    bool isUserLogged() const;
    bool isAdminLogged() const;

    const Vector<Player>& getRanking() const;
    RequestReturnModel<Vector<Admin>> getAdmins() const;
    RequestReturnModel<Vector<Player>> getPlayers() const;

    bool addAdmin(const Admin&);
    bool addPlayer(const Player&);

    AttackResult loggedUserAttack(const MyString& otherName, const MyString& currUserHeroName,
        const MyString& otherUserHeroName);

    bool signIn(const MyString&, const MyString&, UserRole role);
    void logOut();

    void deleteUser(const MyString& name);

    void loadGameFromFile();

    void checkForTurnPaying();
public:
    static Game& getInstance();
    void play();

    inline GameConfig getConfig() const { return _config; }

    ~Game();

    friend class GameMenu;
};

