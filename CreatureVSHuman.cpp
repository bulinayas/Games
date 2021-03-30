#include<iostream>
#include<string>
#include<random>

int getRandomNumber(int a, int b)
{
	std::mt19937_64 gen{ std::random_device()() };
	std::uniform_int_distribution<int> uid(a, b);
	return uid(gen);
}

class Creature 
{
protected:
	std::string m_name;
	char m_symb;
	int m_health;
	int m_damage;
	int m_gold;
public:
	explicit Creature(std::string name="", char symb=' ',int health=0, int damage=0, int gold=0)
		:m_name(name), m_symb(symb),m_health(health),m_damage(damage),m_gold(gold)
	{
	}

	const std::string& getName() const{ return m_name; }
	char getSymb() const { return m_symb; }
	int getHealth() const { return m_health; }
	int getDamage() const { return m_damage; }
	int getGold() const { return m_gold; }

	void reduceHealth(int value) { m_health -= value; }
	bool isDead() { return (m_health <= 0); }
	void addGold(int value) { m_gold += value; }
};

class Player :public Creature
{
private:
	short m_level = 1;
public:
	Player(const std::string& name)
		:Creature(name,'@',10,1,0)
	{
	}

	void levelUp() 
	{
		++m_level;
		++m_damage;
	}

	short getLevel() { return m_level; }
	bool hasWon() { return m_level >= 20; }
};

class Monster : public Creature
{
private:
	struct MonsterData 
	{
		std::string name;
		char symbol;
		int health, damage, gold;
	};
public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};

	static MonsterData monsterData[MAX_TYPES];

	static Type getRandomMonster()
	{
		return (Type)getRandomNumber(0, MAX_TYPES - 1);
	}

	Monster(Type type) 
		:Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health,
			monsterData[type].damage,monsterData[type].gold)
	{
	}

};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'o', 4, 2, 25 },
	{ "slime", 's', 1, 1, 10 }
};

bool runMonster()
{
	if (getRandomNumber(0, 1))
	{
		std::cout << "You successfully fled.\n";
		return true;
	}
	else
	{
		std::cout << "You didn't flee.\n";
		return false;
	}

}

inline void attackMonster(Player& pl, Monster& m)
{
	if (pl.isDead())
		return;

	m.reduceHealth(pl.getDamage());
	std::cout << "You hit the "<<m.getName()<<" for " << pl.getDamage() << " damage.\n";
	if (m.isDead())
	{
		std::cout << "You killed the " << m.getName() << ".\n";
		pl.addGold(m.getGold());
		pl.levelUp();
		std::cout << "You are now level " << pl.getLevel() << ".\n";
		std::cout << "You found " << m.getGold() << " gold.\n";
	}
}

inline void attackPlayer(Player& pl, Monster& m)
{
	if (m.isDead())
		return;
	pl.reduceHealth(m.getDamage());
	std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage.\n";
}

void fightMonster(Player& pl)
{
	char flag{ ' ' };
	bool run{ false };
	Monster m = Monster::getRandomMonster();
	std::cout << "You have encountered a " << m.getName() << " (" << m.getSymb() << ")\n";

	while (!pl.isDead() && !m.isDead() && (run==false)) {

		std::cout << "(R)un or (F)ight:";
		std::cin >> flag;

		if (flag == 'r' || flag == 'R')
		{
			run = runMonster();
			if (!run)
				attackPlayer(pl, m);
		}

		else if (flag == 'f' || flag == 'F')
		{
			attackMonster(pl, m);
			attackPlayer(pl, m);
		}
	}
}

int main()
{
	std::string name;
	std::cout << "Enter your name:";
	std::cin >> name;
	Player player(name);

	std::cout << "Welcome, " << player.getName() << "\n";
	std::cout << "You have " << player.getHealth() << " health and are carrying " << player.getGold() << " gold.\n";
	
	while (!(player.hasWon()) && !(player.isDead())) 
	{
			fightMonster(player);
	}
	if (player.isDead())
		std::cout << "You died at level " << player.getLevel()
		<< " and with " << player.getGold() << " gold.\n Too bad you can't take it with you!\n";
	if(player.hasWon())
		std::cout << "You won at level " << player.getLevel()
		<< " and with " << player.getGold() << " gold.\n Good job!\n";

	return 0;
}