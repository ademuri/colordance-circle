#include "Effect.hpp"

Effect::Effect(std::vector<Pole*> poles) : poles(poles) {}

void Effect::Run() { DoRun(); }
