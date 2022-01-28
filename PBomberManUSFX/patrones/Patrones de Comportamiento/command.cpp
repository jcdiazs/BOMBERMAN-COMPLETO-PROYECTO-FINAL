#include <iostream>
#include <vector>
using namespace std;

// Command interface
class Command {
public:
	virtual ~Command();
	virtual void execute() = 0;
};

Command::~Command() {}

// Receiver
class StockTrade {
public:
	StockTrade() {}
	void buy() { cout << "Buy stock" << endl; }
	void sell() { cout << "Sell stock" << endl; }
};

// Concrete command 1
class BuyOrder : public Command {
	StockTrade* stock;

public:
	BuyOrder(StockTrade* stock);

	void execute() override;
};

BuyOrder::BuyOrder(StockTrade* stock) { this->stock = stock; }

void BuyOrder::execute() { stock->buy(); }

// Concrete command 2
class SellOrder : public Command {
	StockTrade* stock;

public:
	SellOrder(StockTrade* stock);

	void execute() override;
};

SellOrder::SellOrder(StockTrade* stock) { this->stock = stock; }

void SellOrder::execute() { stock->sell(); }

// Invoker
class StockAgent {
public:
	StockAgent();
	void order(Command* command);

private:
	// Looking at this command list gives
	// this order history
	vector<Command*> commandList;
};

StockAgent::StockAgent() {}

void StockAgent::order(Command* command)
{
	commandList.push_back(command);
	command->execute();
}

// Test program
int main()
{
	StockTrade stock;
	BuyOrder buy1(&stock);
	BuyOrder buy2(&stock);
	SellOrder sell1(&stock);

	StockAgent agent;
	agent.order(&buy1);
	agent.order(&buy2);
	agent.order(&sell1);
}