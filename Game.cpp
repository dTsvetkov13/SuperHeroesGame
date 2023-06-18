#include "Game.h"
#include <random>
#include <fstream>;

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

Game::Game()
{
	loadGame();
}

void Game::loadGame()
{
	this->_players = SharedPtr<Vector<Player>>(new Vector<Player>());
	this->_admins = SharedPtr<Vector<Admin>>(new Vector<Admin>());
	this->_graveyard = SharedPtr<Vector<SuperHero>>(new Vector<SuperHero>());

	isNewGame = true;

	if (isNewGame)
	{
		(*_admins).pushBack(Admin("admin", "Admin1"));

		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));
		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));
		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));

		_config.startingMoney = 1000;
		_config.moneyOnDraw = 50;
		_config.moneyOnLose = 200;
		_config.playerMoneyPerTurn = 500;
	}
	else
	{
		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));
		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));
		this->_market.addSuperHero(SuperHero("", "", "Ironman", PowerType::Water, 200, 150, HeroAttackMode::None));
	}
}

void Game::loadGameFromFile()
{
	std::ifstream ifs("Game.txt");

	MyString temp;
	long tempCount;

	ifs >> temp; //Config
	ifs >> _config.playerMoneyPerTurn >> _config.startingMoney 
		>> _config.moneyOnDraw >> _config.moneyOnLose;

	ifs >> temp >> tempCount; //Players

	Player tempPlayer;

	for (int i = 0; i < tempCount; i++)
	{
		ifs >> tempPlayer;
	}

	//TODO: finish reading
}

const Vector<Player>& Game::getRanking() const
{
	Vector<Player> sortedPlayers = *_players;

	Player key;

	for (int i = 1; i < sortedPlayers.getSize(); i++)
	{
		key = sortedPlayers[i];
		int j = i - 1;

		while (j >= 0 && sortedPlayers[j].getBalance() < key.getBalance())
		{
			sortedPlayers[j + 1] = sortedPlayers[j];
			j = j - 1;
		}

		sortedPlayers[j + 1] = key;
	}

	return sortedPlayers;
}

RequestReturnModel<Vector<Admin>> Game::getAdmins() const
{
	return RequestReturnModel<Vector<Admin>>(isAdminLogged(), this->_admins);
}

//Make it return ViewModel
RequestReturnModel<Vector<Player>> Game::getPlayers() const
{
	return RequestReturnModel<Vector<Player>>(true, this->_players);
}

bool Game::addAdmin(const Admin& admin)
{
	if (isAdminLogged())
	{
		(*this->_admins).pushBack(admin);
		return true;
	}
	return false;
}

bool Game::addPlayer(const Player& player)
{
	if (isUserLogged() && !isAdminLogged())
	{
		//error
		return false;
	}
	(*this->_players).pushBack(player);
	return true;
}

void Game::checkForTurnPaying()
{
	int mostLogs = 0;
	int mostLogsPlayersCount = 0;

	for (int i = 0; i < (*_players).getSize(); i++)
	{
		if ((*_players)[i].getTimeLogged() > mostLogs)
		{
			mostLogs = (*_players)[i].getTimeLogged();
			mostLogsPlayersCount = 1;
		}
		else if ((*_players)[i].getTimeLogged() == mostLogs)
		{
			mostLogsPlayersCount++;
		}
	}

	if (mostLogsPlayersCount == 1)
	{
		for (int i = 0; i < (*_players).getSize(); i++)
		{
			(*this->_players)[i].addMoney(this->_config.playerMoneyPerTurn);
		}
	}
}

bool Game::signIn(const MyString& username, const MyString& password, UserRole role)
{
	switch (role)
	{
	case UserRole::Admin:
	{
		for (int i = 0; i < (*_admins).getSize(); i++)
		{
			if ((*_admins)[i].getUserName() == username
				&& (*_admins)[i].getPassword() == password)
			{
				_loggedUser = SharedPtr<User>(new Admin((*_admins)[i]));

				//_loggedUser = SharedPtr<User>((*_admins)[i]);

				return true; //Success
			}
		}
		break;
	}
	case UserRole::Player:
	{
		for (int i = 0; i < (*_players).getSize(); i++)
		{
			if ((*_players)[i].getUserName() == username
				&& (*_players)[i].getPassword() == password)
			{
				_loggedUser = SharedPtr<User>(new Player((*_players)[i]));
				(*_players)[i].logged();
				
				checkForTurnPaying();
				return true; //Success
			}
		}
		break;
	}
	default:
		break;
	}
	

	//Fail
	return false;
}

void Game::logOut()
{
	_loggedUser = nullptr;
	return; // success
}

bool Game::isUserLogged() const
{
	try
	{
		*_loggedUser;
		return true;
	}
	catch (std::runtime_error&)
	{
		return false;
	}
}

bool Game::isAdminLogged() const
{
	if (isUserLogged() && (*_loggedUser).getRole() == UserRole::Admin)
	{
		return true;
	}
	else
	{
		//user not admin
		return false;
	}
}

void Game::play()
{
	GameMenu();
}

void Game::deleteUser(const MyString& name)
{
	bool isAdmin = false;

	if (isAdminLogged() && ((*_loggedUser).getUserName() == name))
	{
		for (int i = 0; i < (*_admins).getSize(); i++)
		{
			if ((*_admins)[i].getUserName() == (*_loggedUser).getUserName())
			{
				(*_admins).popAt(i);
				isAdmin = true;
				break;
			}
		}
	}

	if (!isAdmin)
	{
		if (isAdminLogged() || (((*_loggedUser).getUserName() == name)))
		{
			for (int i = 0; i < (*_players).getSize(); i++)
			{
				if ((*_players)[i].getUserName() == (*_loggedUser).getUserName())
				{
					(*_players).popAt(i);
					break;
				}
			}
		}
	}

	if ((*_loggedUser).getUserName() == name)
	{
		logOut();
	}
}

AttackResult Game::loggedUserAttack(const MyString& otherName, const MyString& currUserHeroName,
	const MyString& otherUserHeroName)
{
	AttackResult result;

	if (isAdminLogged())
	{
		result.hasError = true;
		result.error = "You cannot attack players!";
		return result;
	}

	Player* loggedPlayer = nullptr;
	Player* otherPlayer = nullptr;
	loggedPlayer = static_cast<Player*>(&(*(Game::getInstance()._loggedUser)));

	for (int i = 0; i < (*_players).getSize(); i++)
	{
		if ((*_players)[i].getUserName() == otherName)
		{
			otherPlayer = &(*_players)[i];
			break;
		}
	}

	if (otherPlayer == nullptr)
	{
		result.hasError = true;
		result.error = "Wrong player name!";
		return result;
	}

	SuperHero currHero, otherHero;

	try
	{
		currHero = static_cast<Player*>(&(*_loggedUser))->getSuperHero(currUserHeroName);
	}
	catch (const std::out_of_range&)
	{
		result.hasError = true;
		result.error = "Your hero's name is wrong!";
		return result;
	}

	if (otherPlayer->getSuperHeroes().getSize() <= 0)
	{
		otherPlayer->addMoney(-currHero.getPower());
		loggedPlayer->addMoney(currHero.getPower());//or x
		result.hasError = false;
		result.battlePowerResult = currHero.getPower();
		result.wonMoney = currHero.getPower();
		return result;
	}

	if (otherUserHeroName == "random")
	{
		srand((unsigned)time(NULL));
		int randIndex = std::rand() % otherPlayer->getSuperHeroes().getSize();
		otherHero = otherPlayer->getSuperHeroes()[randIndex];
	}
	else
	{
		try
		{
			otherHero = static_cast<Player*>(&(*_loggedUser))->getSuperHero(otherUserHeroName);
		}
		catch (const std::out_of_range&)
		{
			result.hasError = true;
			result.error = "Other player hero's name is wrong!";
			return result;
		}
	}

	double currentHeroPower = currHero.getPower();
	double otherHeroPower = otherHero.getPower();

	if (otherHero.getPowerType() != currHero.getPowerType())
	{
		if (otherHero.getPowerType() == PowerType::Earth)
		{
			if (currHero.getPowerType() == PowerType::Fire)
			{
				currentHeroPower *= 2;
			}
			else
			{
				otherHeroPower *= 2;
			}
		}
		else if (otherHero.getPowerType() == PowerType::Fire)
		{
			if (currHero.getPowerType() == PowerType::Water)
			{
				currentHeroPower *= 2;
			}
			else
			{
				otherHeroPower *= 2;
			}
		}
		else
		{
			if (currHero.getPowerType() == PowerType::Earth)
			{
				currentHeroPower *= 2;
			}
			else
			{
				otherHeroPower *= 2;
			}
		}
	}
	
	double powerDiff = otherHeroPower - currentHeroPower;

	result.battlePowerResult = powerDiff;

	if (powerDiff < 0)
	{
		powerDiff *= -1;

		(*Game::getInstance()._graveyard).pushBack(otherHero);
		otherPlayer->removeHero(otherHero.getHeroName());
		loggedPlayer->addMoney(powerDiff);

		if (otherHero.getAttackMode() != HeroAttackMode::Defense)
		{
			otherPlayer->addMoney(-powerDiff);
		}

		result.wonMoney = powerDiff;
	}
	else if(powerDiff > 0)
	{
		(*Game::getInstance()._graveyard).pushBack(currHero);
		loggedPlayer->removeHero(currHero.getHeroName());
		loggedPlayer->addMoney(-(powerDiff*2));
		otherPlayer->addMoney(Game::getInstance().getConfig().moneyOnLose); //z

		result.wonMoney = -(powerDiff * 2);
	}
	else
	{
		loggedPlayer->addMoney(-Game::getInstance().getConfig().moneyOnDraw); //k

		result.wonMoney = -Game::getInstance().getConfig().moneyOnDraw;
	}
	
	result.hasError = false;
	
	return result;
}

const MyString& powerTypeToStringForFile(PowerType type)
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

//Will use this to write it to a file
Game::~Game()
{
	std::ofstream ofs("Game.txt");

	ofs << "Config" << std::endl;
	ofs << _config.playerMoneyPerTurn << " " << _config.startingMoney << " " 
		<< _config.moneyOnDraw << " " << _config.moneyOnLose << std::endl;

	ofs << "Players" << (*_players).getSize() <<  std::endl;

	for (int i = 0; i < (*_players).getSize(); i++)
	{
		ofs << (*_players)[i].getUserName()
			<< " !& " << (*_players)[i].getNames()
			<< " !& " << (*_players)[i].getPassword()
			<< " " << (*_players)[i].getEmail()
			<< " " << (*_players)[i].getBalance() << std::endl;
	}

	ofs << "Admins" << (*_admins).getSize() << std::endl;

	for (int i = 0; i < (*_admins).getSize(); i++)
	{
		ofs << (*_admins)[i].getUserName()
			<< " !& " << (*_admins)[i].getNames()
			<< " !& " << (*_admins)[i].getPassword()
			<< " " << (*_admins)[i].getEmail() << std::endl;
	}

	Vector<SuperHero> heroes = _market.getAllSuperHeroes();

	ofs << "Market" << heroes.getSize() << std::endl;

	for (int i = 0; i < heroes.getSize(); i++)
	{
		ofs << heroes[i].getHeroName()
			<< heroes[i].getBuyPrice()
			<< powerTypeToStringForFile(heroes[i].getPowerType())
			<< heroes[i].getPower() << std::endl;
	}

	ofs << "Graveyard" << (*_graveyard).getSize() << std::endl;

	for (int i = 0; i < (*_graveyard).getSize(); i++)
	{
		ofs << (*_graveyard)[i].getHeroName()
			<< (*_graveyard)[i].getBuyPrice()
			<< powerTypeToStringForFile((*_graveyard)[i].getPowerType())
			<< (*_graveyard)[i].getPower() << std::endl;
	}
}