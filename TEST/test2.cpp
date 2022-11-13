#include <iostream>
using namespace std;

class CPlayer {
public:
	virtual ~CPlayer() = default;
	void f() {
		cout << "CPlayer\n";
	}
};

// class CAmazon : public CPlayer {
// public:
// 	CAmazon() { ++counter; }
// 	~CAmazon() { --counter; }
// 	static size_t TotalNumPlayers() {
// 		return counter;
// 	}
// 	static size_t counter;
// };

// size_t CAmazon::counter = 0;

// class CPaladin : public CPlayer {
// public:
// 	CPaladin() { ++counter; }
// 	~CPaladin() { --counter; }
// 	static size_t TotalNumPlayers() {
// 		return counter;
// 	}
// 	static size_t counter;
// };

// size_t CPaladin::counter = 0;

class CSorceress : public CPlayer {
public:
	CSorceress() { ++counter; }
	~CSorceress() { --counter; }
	static size_t TotalNumPlayers() {
		return counter;
	}
	void f() {
		cout << "CSor\n";
	}
	static size_t counter;
};

size_t CSorceress::counter = 0;

class CC : public CSorceress {
public:
	~CC() {};
};

void DisplayNumOfPlayer() {
	// cout << "We have " << CAmazon::TotalNumPlayers() << " amazons, "
	// 				<< CPaladin::TotalNumPlayers() << " paladins, and "
	// 				<< CSorceress::TotalNumPlayers() << " sorceress." << endl;
}

int main() {
	CSorceress csr;
	csr.f();
	// DisplayNumOfPlayer();

	// CPlayer *p[3] = {new CAmazon, new CPaladin, new CSorceress};

	// DisplayNumOfPlayer();

	// if (1)
	// {
	// 	CAmazon lisa;
	// 	CPaladin tmp[2];

	// 	DisplayNumOfPlayer();
	// }

	// DisplayNumOfPlayer();

	// delete p[0];
	// DisplayNumOfPlayer();
}