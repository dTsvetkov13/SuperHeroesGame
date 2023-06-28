#include "GameMenu.h";
#include "MyString.h";
#include "Game.h"
#include "Vector.hpp";
#include "RequestReturnModel.hpp";

#include <iostream>;
#include <string>;
#include "Validator.h"


GameMenu::GameMenu() {}

Vector<MyString> split(const char* str, char delimiter)
{
	Vector<MyString> result;
	char buff[1024];
	size_t buffSize = 0;

	while (*str)
	{
		if (*str == delimiter)
		{
			buff[buffSize] = '\0';
			buffSize = 0;
			result.pushBack(MyString(buff));
		}
		else
		{
			buff[buffSize++] = *str;
		}
		str++;
	}

	if (buffSize > 0)
	{
		result.pushBack(MyString(buff));
	}

	return result;
}

PowerType getType(const MyString& type)
{
	//Here we can use tolower(), but I suggest that it's not allowed
	if (type == "Earth" || type == "earth")
	{
		return PowerType::Earth;
	}
	else if (type == "Fire" || type == "fire")
	{
		return PowerType::Fire;
	}
	else if (type == "Water" || type == "water")
	{
		return PowerType::Water;
	}
	else
	{
		throw std::invalid_argument("");
	}
}

void GameMenu::addPlayerFromMenu() const
{
	char nameBuff[100];
	MyString name, username, password;

	std::cout << "Name: ";
	std::cin.getline(nameBuff, 100);
	name = MyString(nameBuff);

	std::cout << "Username: ";
	std::cin >> username;
	if (!Validator().validateUsername(username))
	{
		std::cout << "Enter valid username! (only lower case and max 16 symbols)" << std::endl;
		return;
	}

	std::cout << "Password: ";
	std::cin >> password;
	if (!Validator().validatePassword(password))
	{
		std::cout << "Enter valid password! (at least one lower, upper and digit)" << std::endl;
		return;
	}
	
	if (Game::getInstance().addPlayer(Player(name, username, password)))
	{
		std::cout << "Player added!" << std::endl;
	}
	else
	{
		std::cout << "Try again!" << std::endl;
	}
}

MyString powerTypeToString(PowerType type)
{
	switch (type)
	{
	case(PowerType::Fire):
	{
		return "Fire";
	}
	case(PowerType::Earth):
	{
		return "Earth";
	}
	case(PowerType::Water):
	{
		return "Water";
	}
	default:
		return "none";
	}
}

bool GameMenu::addHero() const
{
	MyString name, powerType;
	double power, buyPrice;

	std::cout << "Enter hero name: ";
	std::cin >> name;
	std::cout << "Enter hero power type (Earth, Fire or Water): ";
	std::cin >> powerType;
	std::cout << "Enter hero power: ";
	std::cin >> power;
	std::cout << "Enter hero buy price: ";
	std::cin >> buyPrice;

	PowerType type;

	try
	{
		 type = getType(powerType);
	}
	catch (const std::invalid_argument&)
	{
		std::cout << "Wrong power type!" << std::endl;
		return false;
	}

	Game::getInstance()._market.addSuperHero(
		SuperHero("", "", name, type, power, buyPrice, HeroAttackMode::None));

	return true;
}

void GameMenu::startMenuOperation(const MyString& operation) const
{
	/*if (operation == "sign up as admin" || operation == "sua")
	{
		char nameBuff[100];
		MyString name, username, password;

		std::cout << "Name: ";
		std::cin.getline(nameBuff, 100);
		name = MyString(nameBuff);

		std::cout << "Username: ";
		std::cin >> username;
		if (!Validator().validateUsername(username))
		{
			std::cout << "Enter valid username! (only lower case and max 16 symbols)" << std::endl;
			return;
		}

		std::cout << "Password: ";
		std::cin >> password;
		if (!Validator().validatePassword(password))
		{
			std::cout << "Enter valid password! (at least one lower, upper and digit)" << std::endl;
			return;
		}

		Game::getInstance().addAdmin(Admin(name, username, password));
	}*/
	if (operation == "sign up as player" || operation == "sup")
	{
		addPlayerFromMenu();
	}
	else if (operation == "sign in as admin" || operation == "sia")
	{
		MyString username, password;

		std::cout << "Username: ";
		std::cin >> username;

		std::cout << "Password: ";
		std::cin >> password;

		if(Game::getInstance().signIn(username, password, UserRole::Admin))
		{
			std::cout << "Succesfully logged!" << std::endl;
		}
		else
		{
			std::cout << "Try again!" << std::endl;
		}
	}
	else if (operation == "sign in as player" || operation == "sip")
	{
		MyString username, password;

		std::cout << "Username: ";
		std::cin >> username;

		std::cout << "Password: ";
		std::cin >> password;

		if (Game::getInstance().signIn(username, password, UserRole::Player))
		{
			std::cout << "Succesfully logged!" << std::endl;
		}
		else
		{
			std::cout << "Try again!" << std::endl;
		}
	}
	else if (operation == "exit")
	{
		std::cout << "Thank you! See ya!" << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "Invalid operation!" << std::endl;
	}
}

void GameMenu::addHeroesWhenMarketEmpty() const
{
	MyString choice;

	std::cout << "As admin you should add 3 heroes when the market is empty!" << std::endl;

	while (Game::getInstance()._market.getAllSuperHeroes().getSize() < 3)
	{
		std::cout << "You can add new one or pick from already dead ones. Your choice ('pick' or 'add'): ";
		std::cin >> choice;

		if (choice == "pick")
		{
			Vector<SuperHero> graveyard = Game::getInstance().getVector(Game::getInstance()._graveyard);
			unsigned heroNum = 1;

			if (graveyard.getSize() <= 0)
			{
				std::cout << "There are no heroes in graveyard!" << std::endl;
				continue;
			}

			std::cout << "Already dead heroes: ";

			for (int i = 0; i < graveyard.getSize(); i++)
			{
				std::cout << i + 1 << " name: " << graveyard[i].getHeroName()
					<< " power: " << graveyard[i].getPower()
					<< " type: " << powerTypeToString(graveyard[i].getPowerType())
					<< " power: " << graveyard[i].getBuyPrice() << std::endl;
			}

			std::cout << "You can pick one by writing its number: ";
			std::cin >> heroNum;

			if (heroNum > graveyard.getSize())
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Wrong num. Try again!" << std::endl;
				continue;
			}

			Game::getInstance()._market.addSuperHero(graveyard[heroNum - 1]);
			(Game::getInstance()._graveyard).popAt(heroNum - 1);

			std::cout << "\x1B[2J\x1B[H";

			std::cout << "Succesfully added hero!" << std::endl;
		}
		else if (choice == "add")
		{
			std::cout << "Add hero: " << std::endl;
			if (addHero())
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Hero added!" << std::endl;
			}
			else
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Invalid hero data!" << std::endl;
			}
		}
		else
		{
			std::cout << "Wrong input! Try again!" << std::endl;
		}
	}

	std::cout << "Thank you!" << std::endl;

	
}

void GameMenu::showLoggedUserMenu() const
{
	if (Game::getInstance().isAdminLogged())
	{
		if ((Game::getInstance()._market).getAllSuperHeroes().getSize() <= 0)
		{
			addHeroesWhenMarketEmpty();
		}

		std::cout << "1. add admin" << std::endl
			<< "2. add player" << std::endl
			<< "3. delete player" << std::endl
			<< "4. show players" << std::endl
			<< "5. show admins" << std::endl
			<< "6. add hero" << std::endl
			<< "7. logout" << std::endl
			<< "Your choice: ";
	}
	else
	{
		std::cout << "1. show balance" << std::endl
			<< "2. show market" << std::endl
			<< "3. show players" << std::endl
			<< "4. attack <name>" << std::endl
			<< "5. set to defense" << std::endl
			<< "6. set to attack" << std::endl
			<< "7. buy" << std::endl
			<< "8. logout" << std::endl
			<< "9. delete" << std::endl
			<< "10. show ranking" << std::endl
			<< "Your choice: ";
	}
}


void GameMenu::adminOperations(const MyString& operation) const
{
	if (operation == "add admin")
	{
		std::cout << "Performing add admin operation..." << std::endl;

		char nameBuff[100];
		MyString name, username, password;

		std::cout << "Name: ";
		std::cin.getline(nameBuff, 100);
		name = MyString(nameBuff);

		std::cout << "Username: ";
		std::cin >> username;
		if (!Validator().validateUsername(username))
		{
			std::cout << "Enter valid username! (only lower case and max 16 symbols)" << std::endl;
			return;
		}

		std::cout << "Password: ";
		std::cin >> password;
		if (!Validator().validatePassword(password))
		{
			std::cout << "Enter valid password! (at least one lower, upper and digit)" << std::endl;
			return;
		}

		Game::getInstance().addAdmin(Admin(name, username, password));
	}
	else if (operation == "add player")
	{
		std::cout << "Add player" << std::endl;

		addPlayerFromMenu();
	}
	else if (operation == "delete player")
	{
		std::cout << "Delete player" << std::endl;
		
		MyString name;

		std::cout << "Enter player name: ";
		std::cin >> name;

		Game::getInstance().deleteUser(name);
	}
	else if (operation == "show players")
	{
		std::cout << "Show players" << std::endl;

		RequestReturnModel<Vector<Player>> result = Game::getInstance().getPlayers();

		if (result.isAccepted)
		{
			for (int i = 0; i < (*result.data).getSize(); i++)
			{
				std::cout << i+1 << ". " << (*result.data)[i].getUserName()
							<< " " << (*result.data)[i].getNames()
							<< " " << (*result.data)[i].getEmail()
							<< " " << (*result.data)[i].getBalance();

				//heroes
				Player* currPlayer = static_cast<Player*>(&((*result.data)[i]));
				size_t heroesSize = currPlayer->getSuperHeroes().getSize();
				for (int j = 0; j < heroesSize; j++)
				{
					std::cout << i+1 << "." << j+1 << " "
						<< currPlayer->getSuperHeroes()[j].getHeroName()
						<< " " << powerTypeToString(currPlayer->getSuperHeroes()[j].getPowerType());
				}

				std::cout << std::endl;
			}

			if ((*result.data).getSize() <= 0)
			{
				std::cout << "There are no players to show!" << std::endl;
			}
		}
	}
	else if (operation == "show admins")
	{
		std::cout << "Show admins" << std::endl;

		RequestReturnModel<Vector<Admin>> result = Game::getInstance().getAdmins();

		if (result.isAccepted)
		{
			if ((*result.data).getSize() <= 1)
			{
				std::cout << "There are no admins to show!" << std::endl;
				return;
			}

			for (int i = 0; i < (*result.data).getSize(); i++)
			{
				std::cout << i + 1 << ". "
					<< " " << (*result.data)[i].getNames()
					<< " " << (*result.data)[i].getEmail();

				std::cout << std::endl;
			}
		}
	}
	else if (operation == "add hero")
	{
		std::cout << "Add hero" << std::endl;

		addHero();

		std::cout << "Hero added!" << std::endl;
	}
	else
	{
		std::cout << "Invalid operation." << std::endl;
	}
}

void GameMenu::playerOperations(const MyString& operation) const
{
	if (operation == "show balance")
	{
		std::cout << "Show balance" << std::endl;
		std::cout << Game::getInstance().getLoggedPlayerBalance() << std::endl;
	}
	else if (operation == "show market")
	{
		std::cout << "Show market" << std::endl;

		Vector<SuperHero> heroes = Game::getInstance()._market.getAllSuperHeroes();

		for (int i = 0; i < heroes.getSize(); i++)
		{
			std::cout << i+1 << ". name: " << heroes[i].getHeroName()
				<< " price: " << heroes[i].getBuyPrice()
				<< " type: " << powerTypeToString(heroes[i].getPowerType())
				<< " power: " << heroes[i].getPower() << std::endl;
		}

		if (heroes.getSize() <= 0)
		{
			std::cout << "There are no heroes to show!" << std::endl;
		}
	}
	else if (operation == "show players")
	{
		std::cout << "Show players" << std::endl;

		RequestReturnModel<Vector<Player>> result = Game::getInstance().getPlayers();
	
		bool isLoggedPlayerInResult = false;
		int playerCount = 1;

		if (result.isAccepted)
		{
			for (int i = 0; i < (*result.data).getSize(); i++, playerCount++)
			{
				if ((*result.data)[i].getUserName() == (*Game::getInstance()._loggedUser).getUserName())
				{
					isLoggedPlayerInResult = true;
					playerCount--;
					continue;
				}

				std::cout << playerCount << ". " << (*result.data)[i].getUserName()
							<< " " << (*result.data)[i].getBalance() << std::endl;
				//heroes
				Player* currPlayer = static_cast<Player*>(&((*result.data)[i]));
				size_t heroesSize = currPlayer->getSuperHeroes().getSize();
				for (int j = 0; j < heroesSize; j++)
				{
					std::cout << playerCount << "." << j+1 << " "
						<< currPlayer->getSuperHeroes()[j].getHeroName()
						<<  " " << powerTypeToString(currPlayer->getSuperHeroes()[j].getPowerType());
				}

				std::cout << std::endl;
			}

			if ((*result.data).getSize() <= 0 
				|| (isLoggedPlayerInResult && (*result.data).getSize() == 1))
			{
				std::cout << "There are no players to show!" << std::endl;
			}
		}
	}
	else if (operation == "set to attack")
	{
		std::cout << "Set to attack mode" << std::endl;

		MyString heroName;
		std::cout << "Enter the superhero you want to set to attack: ";
		std::cin >> heroName;

		Game::getInstance().changeLoggedUserSuperHeroAttackMode(heroName, HeroAttackMode::Attack);

		std::cout << heroName << " set to attack successfully!" << std::endl;
	}
	else if (operation == "set to defense")
	{
		std::cout << "Set to defense mode" << std::endl;

		MyString heroName;
		std::cout << "Enter the superhero you want to set to defense: ";
		std::cin >> heroName;

		Game::getInstance().changeLoggedUserSuperHeroAttackMode(heroName, HeroAttackMode::Defense);

		std::cout << heroName << " set to defence successfully!" << std::endl;
	}
	else if (operation == "buy")
	{
		std::cout << "Buy hero" << std::endl;

		MyString superHeroName;

		std::cout << "Enter Superhero name from the market you wish to buy: " << std::endl;
		std::cin >> superHeroName;
		
		MarketSaleResult saleResult = Game::getInstance().buySuperHero(superHeroName);

		if (saleResult.hasError)
		{
			std::cout << saleResult.error << std::endl;
		}
		else
		{
			std::cout << "Successfully bought!" << std::endl;
		}
	}
	else if (operation == "delete")
	{
		std::cout << "Delete me" << std::endl;

		Game::getInstance().deleteUser((*Game::getInstance()._loggedUser).getUserName());
		std::cout << "Successfully deleted!" << std::endl;
	}
	else if (operation == "show ranking")
	{
		std::cout << "Show ranking" << std::endl;

		Vector<Player> ranking = Game::getInstance().getRanking();

		for (int i = 0; i < ranking.getSize(); i++)
		{
			std::cout << i + 1 << ". " << ranking[i].getUserName()
				<< " " << ranking[i].getBalance() << std::endl;
		}

		std::cout << std::endl;
	}
	else
	{
		static MyString attackString = MyString("attack");

		if ((operation.length() > attackString.length())
			&& (operation.substr(0, attackString.length()) == attackString))
		{
			std::cout << "Attack player" << std::endl;

			RequestReturnModel<Vector<Player>> playersInGame = Game::getInstance().getPlayers();
			
			if (playersInGame.isAccepted && ((*playersInGame.data).getSize() == 1))
			{
				std::cout << "There are no players to attack now!" << std::endl;
				return;
			}

			MyString name = operation.substr(attackString.length() + 1, operation.length() - (attackString.length() + 1));
			MyString currentSuperHeroName, otherSuperHeroName;

			if (name == "")
			{
				std::cout << "Enter valid player name!" << std::endl;
				return;
			}

			std::cout << "Performing attack on player: " << name << std::endl;

			std::cout << "Enter the superhero you want to attack with: ";
			std::cin >> currentSuperHeroName;

			std::cout << "Enter the superhero you want to attack (or write 'random' for random one): ";
			std::cin >> otherSuperHeroName;

			AttackResult result = Game::getInstance().loggedUserAttack(name, currentSuperHeroName, otherSuperHeroName);

			if (!result.hasError)
			{
				if (result.battlePowerResult == 0)
				{
					std::cout << "You are equal! You have lost: " << -1 * result.wonMoney << "!" << std::endl;
				}
				else if (result.wonMoney > 0)
				{
					std::cout << "Congratulations you have won! You have earned " << result.wonMoney << "!" << std::endl;
				}
				else
				{
					std::cout << "You have lost! You have lost: " << -1 * result.wonMoney << "!" << std::endl;
				}
			}
			else
			{
				std::cout << result.error << std::endl;
				std::cout << "Enter valid data to attack!" << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid operation!" << std::endl;
		}
	}
}

void GameMenu::loggedUserMenuOperation(const MyString& operation) const
{
	if (operation == "logout")
	{
		Game::getInstance().logOut();
		std::cout << "You have logged out successfully!" << std::endl;
		return;
	}

	if (Game::getInstance().isAdminLogged())
	{
		adminOperations(operation);
	}
	else
	{
		playerOperations(operation);
	}
}

void GameMenu::menu() const
{
	std::cout << "Welcome to Super Heroes Game!" << std::endl;

	MyString operation;
	char buff[1024];

	Game::getInstance().isNewGame = false;

	if (Game::getInstance().isNewGame)
	{
		std::cout << "It is a new game, so you have to add 3 heroes. You are logged in as admin! Username and password: <admin, Admin1>." << std::endl;

		std::cout << "But before that, you should configure the game: " << std::endl;
		while (true)
		{
			try
			{
				gameConfig();
				break;
			}
			catch (...)
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Try again" << std::endl;
			}
		}
		
		if (Game::getInstance()._market.getAllSuperHeroes().getSize() < Game::getInstance().MINIMUM_HEROES_COUNT)
		{
			std::cout << "Now heroes: " << std::endl;
		}

		Game::getInstance().signIn("admin", "Admin1", UserRole::Admin);

		while (Game::getInstance()._market.getAllSuperHeroes().getSize() < Game::getInstance().MINIMUM_HEROES_COUNT)
		{
			std::cout << "Add hero: " << std::endl;
			if (addHero())
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Hero added!" << std::endl;
			}
			else
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Invalid hero data!" << std::endl;
			}
		}

		std::cout << "Thank you!" << std::endl;
	}

	while (true)
	{
		std::cout << "Menu (select operation):" << std::endl;

		if (Game::getInstance().isUserLogged())
		{
			showLoggedUserMenu();
			std::cin.seekg(0, std::ios::end);
			std::cin.clear();
			std::cin.getline(buff, 1024);

			std::cout << "\x1B[2J\x1B[H";

			loggedUserMenuOperation(MyString(buff));
		}
		else
		{
		//	std::cout << "1. sign up as admin (shortcut: sua)" << std::endl 
			std::cout << "1. sign up as player (shortcut: sup)" << std::endl
						<< "2. sign in as admin (shortcut: sia)" << std::endl
						<< "3. sign in as player (shortcut: sip)" << std::endl
						<< "4. exit" << std::endl
						<< "Your choice: ";

			std::cin.seekg(0, std::ios::end);
			std::cin.clear();
			std::cin.getline(buff, 1024);

			std::cout << "\x1B[2J\x1B[H";

			startMenuOperation(buff);

			buff[0] = '\0';
		}

		std::cout << std::endl;
	}
}


void GameMenu::gameConfig() const
{
	double playerMoneyPerTurn;
	double moneyOnLose;
	double moneyOnDraw;
	double startingMoney;

	std::cout << "Enter money per turn for players: ";
	std::cin >> (Game::getInstance()._config).playerMoneyPerTurn;

	std::cout << "Enter money on lose: ";
	std::cin >> (Game::getInstance()._config).moneyOnLose;

	std::cout << "Enter money on draw: ";
	std::cin >> (Game::getInstance()._config).moneyOnDraw;

	std::cout << "Enter starting money: ";
	std::cin >> (Game::getInstance()._config).startingMoney;
}