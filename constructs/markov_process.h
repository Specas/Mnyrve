#ifndef MARKOV_PROCESS_H
#define MARKOV_PROCESS_H
#endif

#include "common/domain_types.h"

namespace mnyrve {
namespace constructs {

class MarkovProcess {

  public:
    MarkovProcess(mnyrve::common::types::DomainType state_domain_type);
    mnyrve::common::types::DomainType get_state_domain_type();

  private:
    mnyrve::common::types::DomainType state_domain_type_;


};




} // namespace constructs
} // namespace mnyrve
