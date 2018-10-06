#include "constructs/markov_process.h"

using mnyrve::common::types::DomainType;

namespace mnyrve {
namespace constructs {

  MarkovProcess::MarkovProcess(DomainType state_domain_type):
    state_domain_type_{state_domain_type} {}

  DomainType MarkovProcess::get_state_domain_type() {
    return state_domain_type_;
  }





} // namespace constructs
} // namespace mnyrve
