#include "ProfileCreator.h"

using namespace std;

int main(int argc, char* argv[]){
    ProfileCreator pC = ProfileCreator();
    pC.createProfile("bodyodyyah", "123");
    pC.createProfile("steve", "223");
    pC.createProfile("brgr", "hungry hippo");
    pC.createProfile("slly", "dying");
    pC.displayProfile(0);
    pC.displayProfile(1);
    pC.displayProfile(2);
    pC.displayProfile(3);


}