#ifndef REPLACEMENT_HPP
#define REPLACEMENT_HPP

#include "Position.hpp"
#include "IndividualStats.hpp"
#include "OnIceStats.hpp"
#include "Situation.hpp"

class PlayerDatabase;

class Replacement {
public:
  Replacement(PlayerDatabase &pdb): pdb(pdb) { }
  void initialize();

  IndividualStats &Individual(Situation sit, Position pos);
  OnIceStats &OnIce(Situation sit, Position pos);
private:
  PlayerDatabase &pdb;
  IndividualStats ev_fwd_ind, ev_def_ind, pp_fwd_ind, pp_def_ind, sh_fwd_ind, sh_def_ind, ev_goal_ind, pp_goal_ind, sh_goal_ind;
  OnIceStats ev_fwd_ice, ev_def_ice, pp_fwd_ice, pp_def_ice, sh_fwd_ice, sh_def_ice, ev_goal_ice, pp_goal_ice, sh_goal_ice;
};

#endif // REPLACEMENT_HPP
