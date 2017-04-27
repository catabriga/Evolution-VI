#include "GeneticCode.h"

#include <random>
#include <iostream>

static std::mt19937 rng;
static std::uniform_real_distribution<float> randFloat(0, 1);
static std::uniform_int_distribution<int8_t> randInt5(-5,5);


static void initRandomGenerators(void)
{
	static bool randInitialized = false;

	if(randInitialized == false)
	{
		rng.seed(std::random_device()());
	}
}

static float getRandomFloat(void)
{
	return randFloat(rng);
}

static int8_t getRandomInt5(void)
{
	return randInt5(rng);
}

GeneticCode::GeneticCode(void)
{
	initRandomGenerators();

	for(uint32_t i=0; i<MAX_CODE_SIZE; i++)
	{
		code[i] = 0;
	}
}

GeneticCode::~GeneticCode(void)
{

}

static uint8_t sumNoOverflows(uint8_t a, int8_t b)
{
	if(b > 0)
	{
		if(UINT8_MAX - a < b)
		{
			return UINT8_MAX;
		}
	}
	else
	{
		if(a < b)
		{
			return 0;
		}
	}

	return a + b;
}


static uint8_t hexToNum(char c)
{
	if(c >= 'A')
	{
		return c-'A' + 10;
	}
	else
	{
		return c - '0';
	}
}

static uint8_t doubleHexToNum(char c1, char c2)
{
	return (hexToNum(c1) << 4) + hexToNum(c2);
}

void GeneticCode::initFromString(std::string codeString)
{
	uint32_t i;
	uint32_t j=0;
	for(i=0; (i+1)<codeString.length(); i+=2)
	{
		char c1 = codeString.at(i);
		char c2 = codeString.at(i+1);

		uint8_t gene = doubleHexToNum(c1,c2);
		code[j] = gene;
		j++;
	}

	for(; j<MAX_CODE_SIZE; j++)
	{
		code[j] = 0;
	}
}

void GeneticCode::initFromParent(GeneticCode* parentCode)
{
	for(uint32_t i=0; i<MAX_CODE_SIZE; i++)
	{
		uint8_t gene = parentCode->readGene(i);

		if(getRandomFloat() < GENE_MUTATION_PROBABILITY)
		{
			int8_t mutation = getRandomInt5();
			gene = sumNoOverflows(gene, mutation);
		}

		code[i] = gene;
	}
}

uint8_t GeneticCode::readGene(uint32_t location)
{
	uint32_t index = location % MAX_CODE_SIZE;

	return code[index];
}

