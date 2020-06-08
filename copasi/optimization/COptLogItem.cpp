// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 *  COptLogItem class
 *  Container for a log message created by the copasi optimization methods.
 *  Stores various variable for later compilation of a message string.
 *
 *  Created for COPASI by Jonas F�rster 2013
 */

#include "COptLogItem.h"
#include "copasi/utilities/utility.h"

const std::string COptLogItem::MsgIDHeader[] =
{
  //Std_start
  "Algorithm started at %_timestamp%.",
  //STD_start_nodoc
  "Algorithm started at %_timestamp%.",
  //STD_early_stop
  "Algorithm was terminated preemptively after initial population creation.",
  //STD_finish
  "Algorithm finished at %_timestamp%.",
  //STD_finish_x_of_max_iter
  "Algorithm finished at %_timestamp%.",
  //STD_finish_x_of_max_gener
  "Algorithm finished at %_timestamp%.",
  //STD_finish_temp_info
  "Algorithm finished at %_timestamp%.",
  //STD_initial_point_out_of_Domain
  "Initial point not within parameter domain.",

  //PS_usrdef_error_swarm_size
  "User defined Swarm Size too small. Reset to minimum: %s%.",
  //PS_info_informants
  "Minimal number of informants per particle is %s% at a swarm size of %s% particles.",
  //PS_no_particle_improved
  "Iteration %_iteration%: None of the particles improved in objective function value.",
  //PS_stddev_lower_than_tol_termination
  "Iteration %_iteration%: Standard deviation of the particles was lower than tolerance. Terminating.",

  //SA_steps_per_temp
  "Steps at one single temperature: %s%.",
  //SA_fval_progress_lower_than_tol
  "Temperature step %_iteration%: Objective function value progression for last %s% temperatures was lower than the tolerance.",
  //SA_fval_tol_termination
  "Temperature step %_iteration%: Objective function value didn't progress from optimum by more than the tolerance. Terminating.",

  //DE_usrdef_error_pop_size
  "User defined Population Size too small. Reset to minimum: %s%.",
  //DE_fittest_not_changed_x_random_generated
  "Generation %_iteration%: Fittest individual has not changed for the last %s% generations. %s%% random individuals created.",

  //GA_fittest_not_changed_x_random_generated
  "Generation %_iteration%: Fittest individual has not changed for the last %s% generations. %s%% random individuals created.",

  //GASR_usrdef_error_pf
  "User defined Pf not in interval (0,1). Reset to default: %s%.",
  //GASR_fittest_not_changed_x_random_generated
  "Generation %_iteration%: Fittest individual has not changed for the last %s% generations. %s%% random individuals created.",

  //HJ_steplength_lower_than_tol
  "Iteration %_iteration%: Step length lower than tolerance. Terminating.",

  //LM_hess_pos_def
  "Iteration %_iteration%: Hessian matrix is positive definite. Calculating gradient.",
  //LM_hess_not_pos_def
  "Iteration %_iteration%: Hessian matrix is not positive definite because the leading minor of order %s% is not positive definite.",
  //LM_fval_and_param_change_lower_than_tol
  "Iteration %_iteration%: Objective function value and parameter change lower than tolerance (%s%/3). Resetting lambda.",
  //LM_fval_and_param_change_lower_than_tol_termination
  "Iteration %_iteration%: Objective function value and parameter change lower than tolerance  (%s%/3). Terminating.",
  //LM_lambda_max_termination
  "Iteration %_iteration%: Lambda reached max value. Terminating.",
  //LM_inc_lambda
  "Iteration %_iteration%: Restarting iteration with increased lambda.",
  //LM_count_edge_of_param_domain
  "Algorithm reached the edge of the parameter domain %s% times.",

  //CW_min_step_size
  "Minimum step size is %s%.",

  //NM_fval_change_lower_than_tol
  "Iteration %_iteration%: Variance of the objective function values at the vertices of the current simplex lower than tolerance. Checking whether local minimum was found.",
  //NM_local_min_termination
  "Iteration %_iteration%: Local minimum found. Terminating.",
  //NM_no_local_min_reducing_simplex
  "Iteration %_iteration%: No local minimum found. Reducing simplex size.",

  //SRES_usrdef_error_pf
  "User defined Pf not in interval (0,1). Reset to default: %s%.",
  //SRES_fittest_not_changed_x_random_generated
  "Generation %_iteration%: Fittest individual has not changed for the last %s% generations. %s%% random individuals created.",

  //TN_next_repeat
  "Solution parameters outside of the boundaries. Repeating calculations from current border position (%s%/9).",
};

const std::string COptLogItem::MsgIDSubtext[] =
{
  //Std_start
  "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/%s%",
  //STD_start_nodoc
  "",
  //STD_early_stop
  "",
  //STD_finish
  "",
  //STD_finish_x_of_max_iter
  "Terminated after %_iteration% of %s% iterations.",
  //STD_finish_x_of_max_gener
  "Terminated after %_iteration% of %s% generations.",
  //STD_finish_temp_info
  "Final Temperature was %s% after %_iteration% temperature steps.",
  //STD_initial_point_out_of_Domain
  "",

  //PS_usrdef_error_swarm_size
  "",
  //PS_info_informants
  "",
  //PS_no_particle_improved
  "Rebuilding informants with %s% informants per particle.",
  //PS_stddev_lower_than_tol_termination
  "",

  //SA_steps_per_temp
  "",
  //SA_fval_progress_lower_than_tol
  "T = %s%.",
  //SA_fval_tol_termination
  "T = %s%.",

  //DE_usrdef_error_pop_size
  "",
  //DE_fittest_not_changed_x_random_generated
  "",

  //GA_fittest_not_changed_x_random_generated
  "",

  //GASR_usrdef_error_pf
  "",
  //GASR_fittest_not_changed_x_random_generated
  "",

  //HJ_steplength_lower_than_tol
  "",

  //LM_hess_pos_def
  "",
  //LM_hess_not_pos_def
  "",
  //LM_fval_and_param_change_lower_than_tol
  "",
  //LM_fval_and_param_change_lower_than_tol_termination
  "",
  //LM_lambda_max_termination
  "",
  //LM_inc_lambda
  "",
  //LM_count_edge_of_param_domain
  "",

  //CW_min_step_size
  "",

  //NM_fval_change_lower_than_tol
  "",
  //NM_local_min_termination
  "",
  //NM_no_local_min_reducing_simplex
  "",

  //SRES_usrdef_error_pf
  "",
  //SRES_fittest_not_changed_x_random_generated
  "",

  //TN_next_repeat
  "",
};

// Constructor
COptLogItem::COptLogItem(MsgID id, const std::string& statusDump):
  mID(id),
  mTimestamp(time(NULL)),
  mStatusDump(statusDump)
{
  //encountered a Message ID with undefined message string?
  assert(mID < sizeof(MsgIDHeader) / sizeof(MsgIDHeader[0]) && !MsgIDHeader[mID].empty());

  mVarCount = countVars(MsgIDHeader[id]) + countVars(MsgIDSubtext[id]);
}

COptLogItem::~COptLogItem()
{}

COptLogItem & COptLogItem::iter(size_t val)
{
  mIteration = val;

  return *this;
}

COptLogItem::MsgID COptLogItem::getMsgId() const
{
  return mID;
}

time_t COptLogItem::getTimestamp() const
{
  return mTimestamp;
}

std::string COptLogItem::getHeader() const
{
  if (mID < sizeof(MsgIDHeader) / sizeof(MsgIDHeader[0]) && !MsgIDHeader[mID].empty())
    return fillString(MsgIDHeader[mID]);
  else
    return "!Message ID not implemented!";
}

std::string COptLogItem::getSubtext() const
{
  if (mID < sizeof(MsgIDSubtext) / sizeof(MsgIDSubtext[0]) && !MsgIDSubtext[mID].empty())
    return fillString(MsgIDSubtext[mID], countVars(MsgIDHeader[mID]));
  else
    return "";
}

std::string COptLogItem::getStatusDetails() const
{
  return mStatusDump;
}

std::string COptLogItem::fillString(const std::string & inputStr, unsigned C_INT32 varOffset) const
{
  size_t found;
  std::string str = inputStr;

  found = str.find("%_timestamp%");

  while (found != std::string::npos)
    {
      str.replace(found, 12, ISODateTime(localtime(&mTimestamp)));
      found = str.find("%_timestamp%", found + 1);
    }

  found = str.find("%_iteration%");

  while (found != std::string::npos)
    {
      std::stringstream iterStr;
      iterStr << mIteration;

      str.replace(found, 12, iterStr.str());
      found = str.find("%_iteration%", found + 1);
    }

  found = str.find("%s%");

  while (found != std::string::npos)
    {
      if (varOffset < mMsgVars.size())
        {
          str.replace(found, 3, mMsgVars[varOffset]);

          found = str.find("%s%", found + 1);
          ++varOffset;
        }
      else
        {
          assert(false);
          break;
        }
    }

  return str;
}

unsigned C_INT32 COptLogItem::countVars(const std::string & str) const
{
  C_INT32 count = 0;

  for (size_t offset = str.find("%s%"); offset != std::string::npos; offset = str.find("%s%", offset + 1))
    {
      ++count;
    }

  return count;
}
