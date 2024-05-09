#include "Member.h"

using namespace std;

Member::Member() {

}

Member::~Member() {

}

void Member::setID(int value) {
  ID = value;
}

int Member::getID() {
  return ID;
}

string Member::getName() {
  return name;
}

string Member::getLevel() {
  return level;
}
