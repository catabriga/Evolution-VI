#ifndef SRC_GENETICCODE_H_
#define SRC_GENETICCODE_H_

#include <stdint.h>
#include <string>

class GeneticCode
{
public:
	GeneticCode(void);
	virtual ~GeneticCode(void);

	void initFromString(std::string codeString);
	void initFromParent(GeneticCode* parentCode);

	uint8_t readGene(uint32_t location);

private:

	static constexpr float GENE_MUTATION_PROBABILITY = 0.01;

	static const uint32_t MAX_CODE_SIZE = 256;
	uint8_t code[MAX_CODE_SIZE];

};

#endif
