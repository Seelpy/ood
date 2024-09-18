#ifndef IDANCEBEHAVIOR_H
#define IDANCEBEHAVIOR_H

// TODO Какие методы можно было бы добавить и при этом чтобы он оставался одним и тем же


struct IDanceBehavior
{
	virtual ~IDanceBehavior(){};
	virtual void Dance() = 0;
};

#endif
