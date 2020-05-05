#include <iostream>

enum MoveType
{
    PHYSIC,
    SPECIAL
};

struct Move
{
    std::string name;
    int precision, power;
    MoveType type;
};

struct Pokemon
{
    std::string name;
    int attackDmg, specialAtkDmg, defense, specialDefense, speed, hp, xp, chosenMove;
    Move moves[4];
};

void Swap(Pokemon &p1, Pokemon &p2)
{
    Pokemon temp = p1;
    p1 = p2;
    p2 = temp;
}

Pokemon& Fight(Pokemon p1, Pokemon p2)
{
    bool matching = true;
    while(matching)
    {
        //input phase
        for(int j = 0; j < 2; j++)
        {
            std::cout << p1.name <<", scegli una delle seguenti mosse: \n";
            for(int i = 0; i < 4; i++)
            {
                std::cout << i << " - " << p1.moves[i].name << "\n";
            }
            std::cout << "La tua scelta: ";
            std::cin >> p1.chosenMove;
            Swap(p1, p2);
        }

        //il primo pokemon che attacca è il più veloce
        if(p2.speed > p1.speed)
            Swap(p1, p2);

        for(int j = 0; j < 2; j++)
        {
            int damage = (p1.moves[p1.chosenMove].type == MoveType::PHYSIC ?
                         p1.moves[p1.chosenMove].power + p1.attackDmg
                         - p2.defense:
                         p1.moves[p1.chosenMove].power + p1.specialAtkDmg
                         - p2.specialDefense);
            p2.hp -= damage;
            std::cout << p1.name << " ha colpito " << p2.name << " usando "
                    << p1.moves[p1.chosenMove].name << " e ha fatto " <<
                    damage << " danni!\n";
            if(p2.hp <= 0)
            {
                std::cout << p1.name << " ha vinto!\n";
                matching = false;
                break;
            }
            Swap(p1, p2);
        }
    }
}

class Player
{
private:
    std::string m_name;
    std::vector<Pokemon> pokemons;
public:
    Player(std::string _name)
    {
        m_name = _name;
    }
    void AddPokemon(Pokemon pokemon)
    {
        pokemons.push_back(pokemon);
    }
};


int main()
{
    Pokemon Lucario = { "Lucario", 110, 115, 70, 70, 90, 300, 0, 0,
        {
            { "Palmo Forza", 100, 60, MoveType::PHYSIC },
            { "Osso Raffica", 100, 50, MoveType::PHYSIC },
            { "Meteor Mash", 90, 90, MoveType::PHYSIC },
            { "Forza Sfera", 100, 90, MoveType::SPECIAL }
        }
    };
    Pokemon Snorlax = { "Snorlax", 110, 65, 65, 110, 30, 500, 0, 0,
        {
            { "Rutto", 100, 120, MoveType::SPECIAL },
            { "Body Press", 100, 80, MoveType::PHYSIC },
            { "Gigaimpatto", 90, 150, MoveType::PHYSIC },
            { "Fuoco Pugno", 100, 95, MoveType::PHYSIC }
        }
     };
     Pokemon Charizard = { "Charizard", 120, 130, 50, 80, 100, 350, 0, 0,
        {
            { "Lancia fiamme", 100, 90, MoveType::SPECIAL },
            { "Accendino", 100, 50, MoveType::PHYSIC },
            { "Sputa fuoco", 90, 90, MoveType::PHYSIC },
            { "Volo", 100, 90, MoveType::SPECIAL }
        }
    };
    Pokemon Blastoise = { "Blastoise", 110, 65, 65, 110, 30, 500, 0, 0,
        {
            { "Idropompa", 100, 120, MoveType::SPECIAL },
            { "Capocciata", 100, 80, MoveType::PHYSIC },
            { "Pistolacqua", 90, 150, MoveType::PHYSIC },
            { "Forza antica", 100, 95, MoveType::PHYSIC }
        }
     };

    Player p1(3, "Andrea");
    Player p2(2, "Filippo");

    p1.AddPokemon(Lucario);
    p1.AddPokemon(Snorlax);
    p2.AddPokemon(Charizard);
    p2.AddPokemon(Blastoise);

    //Fight(Lucario, Snorlax);

    return 0;
}
