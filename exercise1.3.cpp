#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <stdexcept>

#include <eo>

#include <ga.h>
typedef eoBit<double> Indi;

using namespace std;

double binary_value(const Indi & _indi) {
	double sum = 0;
	for (unsigned i = 0; i < _indi.size(); i++)
		sum += _indi[i];
	return sum;
}

void main_function(int argc, char **argv) {
	const unsigned int SEED = 42;
	const unsigned int VEC_SIZE = 8; 
	const unsigned int POP_SIZE = 20; 
	const unsigned int MAX_GEN = 500; 
	const float CROSS_RATE = 0.8;
	const double P_MUT_PER_BIT = 0.01;
	const float MUT_RATE = 1.0;

	rng.reseed(SEED);

	eoEvalFuncPtr<Indi> eval(  binary_value );


	eoPop<Indi> pop;
	for (unsigned int igeno=0; igeno<POP_SIZE; igeno++) {
		Indi v;
		for (unsigned ivar=0; ivar<VEC_SIZE; ivar++) {
			bool r = rng.flip(); 
			v.push_back(r);
		}
		eval(v);
		pop.push_back(v);
	}

	pop.sort();
	cout << "Initial Population" << endl;
	cout << pop;

	const unsigned int T_SIZE = 3; 
	eoDetTournamentSelect<Indi> select(T_SIZE);       



	eoGenContinue<Indi> continuator(MAX_GEN);


	eoBitMutation<Indi>  mutation(P_MUT_PER_BIT);
	eo1PtBitXover<Indi> xover;



	eoSGA<Indi> gga(select, xover, CROSS_RATE, mutation, MUT_RATE,
				 eval, continuator);

	gga(pop);

	pop.sort();
	cout << "FINAL Population\n" << pop << endl;
}


int main(int argc, char **argv){
	try {
		main_function(argc, argv);
	} catch(exception& e) {
		cout << "Exception: " << e.what() << '\n';
	}
return 1;
}
