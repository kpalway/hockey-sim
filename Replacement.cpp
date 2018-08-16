#include "Replacement.hpp"
#include "Situation.hpp"
#include "PlayerDatabase.hpp"

void Replacement::initialize() {
  // essentially hard-code all the replacement players
  std::vector<std::string> ev_fwd = {"Adam Cracknell", "Joseph Blandisi", "Kyle Rau",
    "Colby Cave", "Steve Bernier", "Kerby Rychel", "Hudson Fasching", "Jared Boll",
    "Ryan Lomberg", "Janne Kuokkanen", "Michael Bournival"};
  std::vector<std::string> ev_def = {"Zach Trotman", "Carson Soucy", "Zach Redmond",
    "Calle Rosen", "Dalton Prout", "Joel Hanley", "Frank Corrado",
    "Dillon Heatherington", "Blake Hillman", "Joe Hicketts", "Chris Butler"};
  std::vector<std::string> goal = {"Maxime Lagace", "Oscar Dansk", "Casey DeSmith"};
  std::vector<std::string> pp_fwd = {"Jujhar Khaira", "Jake Virtanen", "Chris Stewart",
    "Ty Rattie", "Nick Cousins", "Nicholas Baptiste", "Chris Wagner", "Frank Vatrano"};
  std::vector<std::string> pp_def = {"MacKenzie Weegar", "Sebastian Aho.",
    "Kris Russell", "Marcus Pettersson", "Travis Sanheim", "Rasmus Andersson",
    "Joe Morrow"};
  std::vector<std::string> sh_fwd = {"Peter Holland", "Greg McKegg", "Paul Carey",
    "Dennis Rasmussen", "Lukas Sedlak", "Josh Jooris"};
  std::vector<std::string> sh_def = {"Klas Dahlbeck", "Roman Polak", "Joe Morrow",
    "Jaycob Megna", "Eric Gryba", "Taylor Chorney"};

  for (uint i = 0; i < ev_fwd.size(); i++) {
    Player &p = pdb.lookup(ev_fwd[i]);
    ev_fwd_ind.AddStats(p.LastSeasonIndividual(Situation::EV));
    ev_fwd_ice.AddStats(p.LastSeasonOnIce(Situation::EV));
  }
  for (uint i = 0; i < ev_def.size(); i++) {
    Player &p = pdb.lookup(ev_def[i]);
    ev_def_ind.AddStats(p.LastSeasonIndividual(Situation::EV));
    ev_def_ice.AddStats(p.LastSeasonOnIce(Situation::EV));
  }
  for (uint i = 0; i < pp_fwd.size(); i++) {
    Player &p = pdb.lookup(pp_fwd[i]);
    pp_fwd_ind.AddStats(p.LastSeasonIndividual(Situation::PP));
    pp_fwd_ice.AddStats(p.LastSeasonOnIce(Situation::PP));
  }
  for (uint i = 0; i < pp_def.size(); i++) {
    Player &p = pdb.lookup(pp_def[i]);
    pp_def_ind.AddStats(p.LastSeasonIndividual(Situation::PP));
    pp_def_ice.AddStats(p.LastSeasonOnIce(Situation::PP));
  }
  for (uint i = 0; i < sh_fwd.size(); i++) {
    Player &p = pdb.lookup(sh_fwd[i]);
    sh_fwd_ind.AddStats(p.LastSeasonIndividual(Situation::SH));
    sh_fwd_ice.AddStats(p.LastSeasonOnIce(Situation::SH));
  }
  for (uint i = 0; i < sh_def.size(); i++) {
    Player &p = pdb.lookup(sh_def[i]);
    sh_def_ind.AddStats(p.LastSeasonIndividual(Situation::SH));
    sh_def_ice.AddStats(p.LastSeasonOnIce(Situation::SH));
  }
  for (uint i = 0; i < goal.size(); i++) {
    Player &p = pdb.lookup(goal[i]);
    ev_goal_ind.AddStats(p.LastSeasonIndividual(Situation::EV));
    ev_goal_ice.AddStats(p.LastSeasonOnIce(Situation::EV));
    pp_goal_ind.AddStats(p.LastSeasonIndividual(Situation::PP));
    pp_goal_ice.AddStats(p.LastSeasonOnIce(Situation::PP));
    sh_goal_ind.AddStats(p.LastSeasonIndividual(Situation::SH));
    sh_goal_ice.AddStats(p.LastSeasonOnIce(Situation::SH));
  }
}

static bool isForward(Position pos) {
  return pos == Position::LW || pos == Position::C || pos == Position::RW;
}

static bool isDefense(Position pos) {
  return pos == Position::LD || pos == Position::RD || pos == Position::D;
}

IndividualStats &Replacement::Individual(Situation sit, Position pos) {
  if (sit == Situation::EV) {
    if (isForward(pos)) {
      return ev_fwd_ind;
    }
    if (isDefense(pos)) {
      return ev_def_ind;
    }
    return ev_goal_ind;
  }
  if (sit == Situation::PP) {
    if (isForward(pos)) {
      return pp_fwd_ind;
    }
    if (isDefense(pos)) {
      return pp_def_ind;
    }
    return pp_goal_ind;
  }
  if (isForward(pos)) {
    return sh_fwd_ind;
  }
  if (isDefense(pos)) {
    return sh_def_ind;
  }
  return sh_goal_ind;
}

OnIceStats &Replacement::OnIce(Situation sit, Position pos) {
  if (sit == Situation::EV) {
    if (isForward(pos)) {
      return ev_fwd_ice;
    }
    if (isDefense(pos)) {
      return ev_def_ice;
    }
    return ev_goal_ice;
  }
  if (sit == Situation::PP) {
    if (isForward(pos)) {
      return pp_fwd_ice;
    }
    if (isDefense(pos)) {
      return pp_def_ice;
    }
    return pp_goal_ice;
  }
  if (isForward(pos)) {
    return sh_fwd_ice;
  }
  if (isDefense(pos)) {
    return sh_def_ice;
  }
  return sh_goal_ice;
}
