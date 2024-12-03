#include <iostream>
#include <string>
using namespace std;

class ICharacter {
public:
    virtual void SpecialAbility() = 0;
};

class Human {
protected:
    string name;
    string surname;
    int age;
    string gender;

public:
    Human(const string& n, const string& s, int a, const string& g)
        : name(n), surname(s), age(a), gender(g) {}
        
    string GetName() const { return name; }
    void SetName(const string& n) { name = n; }

    string GetSurname() const { return surname; }
    void SetSurname(const string& s) { surname = s; }

    int GetAge() const { return age; }
    void SetAge(int a) { age = a; }

    string GetGender() const { return gender; }
    void SetGender(const string& g) { gender = g; }
};

class Lumberjack : public Human, public ICharacter {
private:
    string tool;
    int strength;
    string forestLocation;
    int experience;
    bool hasChainsaw;

public:
    Lumberjack(const string& n, const string& s, int a, const string& g, const string& t,
        int str, const string& loc, int exp, bool chainsaw)
        : Human(n, s, a, g), tool(t), strength(str), forestLocation(loc),
        experience(exp), hasChainsaw(chainsaw) {}

    string GetTool() const { return tool; }
    void SetTool(const string& t) { tool = t; }

    int GetStrength() const { return strength; }
    void SetStrength(int str) { strength = str; }

    string GetForestLocation() const { return forestLocation; }
    void SetForestLocation(const string& loc) { forestLocation = loc; }

    int GetExperience() const { return experience; }
    void SetExperience(int exp) { experience = exp; }

    bool HasChainsaw() const { return hasChainsaw; }
    void SetHasChainsaw(bool chainsaw) { hasChainsaw = chainsaw; }

    void SpecialAbility() override {
        cout << name << " uses " << tool << " to cut down trees in the " << forestLocation << " forest." << endl;
    }
};

class Miner : public Human, public ICharacter {
private:
    string equipment;
    int miningSkill;
    string mineLocation;
    int gemsCollected;
    bool hasHelmet;

public:
    Miner(const string& n, const string& s, int a, const string& g, const string& e,
        int skill, const string& loc, int gems, bool helmet)
        : Human(n, s, a, g), equipment(e), miningSkill(skill), mineLocation(loc),
        gemsCollected(gems), hasHelmet(helmet) {}

    string GetEquipment() const { return equipment; }
    void SetEquipment(const string& e) { equipment = e; }

    int GetMiningSkill() const { return miningSkill; }
    void SetMiningSkill(int skill) { miningSkill = skill; }

    string GetMineLocation() const { return mineLocation; }
    void SetMineLocation(const string& loc) { mineLocation = loc; }

    int GetGemsCollected() const { return gemsCollected; }
    void SetGemsCollected(int gems) { gemsCollected = gems; }

    bool HasHelmet() const { return hasHelmet; }
    void SetHasHelmet(bool helmet) { hasHelmet = helmet; }

    void SpecialAbility() override {
        cout << name << " uses " << equipment << " to mine gems in the " << mineLocation << " mine." << endl;
    }
};

class Knight : public Human, public ICharacter {
private:
    string weapon;
    string allegiance;
    int battlesWon;
    bool hasHorse;
    string castleLocation;

public:
    Knight(const string& n, const string& s, int a, const string& g, const string& w,
        const string& all, int battles, bool horse, const string& castle)
        : Human(n, s, a, g), weapon(w), allegiance(all), battlesWon(battles),
        hasHorse(horse), castleLocation(castle) {}

    string GetWeapon() const { return weapon; }
    void SetWeapon(const string& w) { weapon = w; }

    string GetAllegiance() const { return allegiance; }
    void SetAllegiance(const string& all) { allegiance = all; }

    int GetBattlesWon() const { return battlesWon; }
    void SetBattlesWon(int battles) { battlesWon = battles; }

    bool HasHorse() const { return hasHorse; }
    void SetHasHorse(bool horse) { hasHorse = horse; }

    string GetCastleLocation() const { return castleLocation; }
    void SetCastleLocation(const string& castle) { castleLocation = castle; }

    void SpecialAbility() override {
        cout << name << " wields a " << weapon << " and is loyal to " << allegiance << " in the castle at " << castleLocation << "." << endl;
    }
};

class Squire : public Human, public ICharacter {
private:
    string knightName;
    string squireDuty;
    int yearsInService;
    bool isTraining;

public:
    Squire(const string& n, const string& s, int a, const string& g, const string& k,
        const string& duty, int years, bool training)
        : Human(n, s, a, g), knightName(k), squireDuty(duty),
        yearsInService(years), isTraining(training) {}

    string GetKnightName() const { return knightName; }
    void SetKnightName(const string& k) { knightName = k; }

    string GetSquireDuty() const { return squireDuty; }
    void SetSquireDuty(const string& duty) { squireDuty = duty; }

    int GetYearsInService() const { return yearsInService; }
    void SetYearsInService(int years) { yearsInService = years; }

    bool IsTraining() const { return isTraining; }
    void SetIsTraining(bool training) { isTraining = training; }

    void SpecialAbility() override {
        cout << name << " serves as a squire to " << knightName << " and is responsible for " << squireDuty << " duties." << endl;
    }
};

class Archer : public Human, public ICharacter {
private:
    string bowType;
    int arrows;
    string favoriteForest;

public:
    Archer(const string& n, const string& s, int a, const string& g, const string& bow,
        int arrowCount, const string& forest)
        : Human(n, s, a, g), bowType(bow), arrows(arrowCount), favoriteForest(forest) {}

    string GetBowType() const { return bowType; }
    void SetBowType(const string& bow) { bowType = bow; }

    int GetArrowCount() const { return arrows; }
    void SetArrowCount(int count) { arrows = count; }

    string GetFavoriteForest() const { return favoriteForest; }
    void SetFavoriteForest(const string& forest) { favoriteForest = forest; }

    void SpecialAbility() override {
        cout << name << " uses a " << bowType << " and has " << arrows << " arrows in the " << favoriteForest << " forest." << endl;
    }
};

class Mage : public Human, public ICharacter {
private:
    string staffType;
    int mana;
    string favoriteSpell;

public:
    Mage(const string& n, const string& s, int a, const string& g, const string& staff,
        int manaPoints, const string& spell)
        : Human(n, s, a, g), staffType(staff), mana(manaPoints), favoriteSpell(spell) {}

    string GetStaffType() const { return staffType; }
    void SetStaffType(const string& staff) { staffType = staff; }

    int GetManaPoints() const { return mana; }
    void SetManaPoints(int points) { mana = points; }

    string GetFavoriteSpell() const { return favoriteSpell; }
    void SetFavoriteSpell(const string& spell) { favoriteSpell = spell; }

    void SpecialAbility() override {
        cout << name << " wields a " << staffType << " and has " << mana << " mana points for casting " << favoriteSpell << "." << endl;
    }
};

int main() {
    Lumberjack jack("Jack", "Smith", 30, "Male", "Axe", 80, "Greenwood Forest", 5, true);
    Miner mike("Mike", "Johnson", 35, "Male", "Pickaxe", 90, "Stonehill Mine", 50, false);
    Knight arthur("Arthur", "Pendragon", 28, "Male", "Sword", "Camelot", 10, true, "Camelot Castle");
    Squire gawain("Gawain", "Green", 22, "Male", "Arthur Pendragon", "Serving the Knight", 3, true);
    Archer legolas("Legolas", "Greenleaf", 1000, "Male", "Longbow", 100, "Mirkwood Forest");
    Mage gandalf("Gandalf", "Grey", 2019, "Male", "Staff", 10000, "Fireball");

    cout << "Lumberjack's tool: " << jack.GetTool() << endl;
    cout << "Miner's equipment: " << mike.GetEquipment() << endl;
    cout << "Knight's allegiance: " << arthur.GetAllegiance() << endl;
    cout << "Squire's knight: " << gawain.GetKnightName() << endl;
    cout << "Archer's bow type: " << legolas.GetBowType() << endl;
    cout << "Mage's staff type: " << gandalf.GetStaffType() << endl;

    jack.SpecialAbility();
    mike.SpecialAbility();
    arthur.SpecialAbility();
    gawain.SpecialAbility();
    legolas.SpecialAbility();
    gandalf.SpecialAbility();
    return 0;
}
