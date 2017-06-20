#include "Scoreboard.h"

Scoreboard* Scoreboard::creatScoreboard()
{
	Scoreboard* scoreboard = new Scoreboard();
	if (scoreboard)
	{
		for (int i = 0; i < 10; i++)
		{
			scoreboard->push_back('0');
		}

		return scoreboard;
	}
	return nullptr;
}

void Scoreboard::Scoreboard_add_num(std::string num)
{
	int n_2 = 0;
	int num_length = num.size() - 1;
	int this_size = this->size() - 1;
	int adder = 0, carry = 0;
	int temp1 = 0, temp2 = 0;
	int sum;



	for (int i = 0; i <= num_length || carry != 0; i++)
	{

		temp1 = this->at(this_size - i) - '0';
		if (i <= num_length) {
			temp2 = num[num_length - i] - '0';
		}
		else
		{
			temp2 = 0;
		}
		sum = temp1 + temp2 + carry;

		adder = sum % 10;
		carry = sum / 10;
		char ch = adder + '0';
		this->at(this_size - i) = ch;
	}



}