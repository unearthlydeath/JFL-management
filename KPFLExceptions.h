#ifndef KPFLEXCEPTIONS_H
#define KPFLEXCEPTIONS_H

#include <stdexcept>
#include <string>
using namespace std;

// Base class for every KPFL business-rule violation
class KPFLException : public runtime_error
{
public:
    KPFLException(string message) : runtime_error(message) {}
};

// Rule: An unregistered or suspended team cannot be assigned to a fixture
class TeamNotEligibleException : public KPFLException
{
public:
    TeamNotEligibleException(string message) : KPFLException(message) {}
};

// Rules: A team cannot play two fixtures at the same day and time
//        A match official cannot be assigned to conflicting fixtures
class SchedulingConflictException : public KPFLException
{
public:
    SchedulingConflictException(string message) : KPFLException(message) {}
};

// Rule: Match scores and quantities cannot be negative
class NegativeValueException : public KPFLException
{
public:
    NegativeValueException(string message) : KPFLException(message) {}
};

// A team cannot hold more players than its squad limit
class SquadFullException : public KPFLException
{
public:
    SquadFullException(string message) : KPFLException(message) {}
};

// The same team, player, coach or jersey number cannot be added twice
class DuplicateEntryException : public KPFLException
{
public:
    DuplicateEntryException(string message) : KPFLException(message) {}
};

// A search, update or removal referred to something that does not exist
class EntityNotFoundException : public KPFLException
{
public:
    EntityNotFoundException(string message) : KPFLException(message) {}
};

#endif
