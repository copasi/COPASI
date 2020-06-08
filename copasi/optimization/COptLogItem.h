// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_COptLogItem
#define COPASI_COptLogItem

#include <string>
#include <sstream>
#include <vector>
#include <ctime>

#include "copasi/copasi.h"

class COptLogItem
{
  // Attributes
public:
  /**
   * Enumeration of IDs for all messages
   */
  enum MsgID
  {
    STD_start,
    STD_start_nodoc,
    STD_early_stop,
    STD_finish,
    STD_finish_x_of_max_iter,
    STD_finish_x_of_max_gener,
    STD_finish_temp_info,
    STD_initial_point_out_of_domain,

    PS_usrdef_error_swarm_size,
    PS_info_informants,
    PS_no_particle_improved,
    PS_stddev_lower_than_tol_termination,

    SA_steps_per_temp,
    SA_fval_progress_lower_than_tol,
    SA_fval_tol_termination,

    DE_usrdef_error_pop_size,
    DE_fittest_not_changed_x_random_generated,

    GA_fittest_not_changed_x_random_generated,

    GASR_usrdef_error_pf,
    GASR_fittest_not_changed_x_random_generated,

    HJ_steplength_lower_than_tol,

    LM_hess_pos_def,
    LM_hess_not_pos_def,
    LM_fval_and_param_change_lower_than_tol,
    LM_fval_and_param_change_lower_than_tol_termination,
    LM_lambda_max_termination,
    LM_inc_lambda,
    LM_count_edge_of_param_domain,

    CW_min_step_size,

    NM_fval_change_lower_than_tol,
    NM_local_min_termination,
    NM_no_local_min_reducing_simplex,

    SRES_usrdef_error_pf,
    SRES_fittest_not_changed_x_random_generated,

    TN_next_repeat
  };

  /**
   * Vector of message headers for all defined MsgIDs
   */
  static const std::string MsgIDHeader[];

  /**
   * Vector of message subtexts for all defined MsgIDs
   */
  static const std::string MsgIDSubtext[];

protected:
  /**
   * Message ID for this log item.
   */
  MsgID mID;

  /**
   * Amount of variables for this log item.
   */
  unsigned C_INT32 mVarCount;

  /**
   * Timestamp for this log item.
   */
  time_t mTimestamp;

  /**
   * Iteration that this log item was created at (optional).
   */
  size_t mIteration;

  /**
   * All further variables fed into this log item (optional).
   */
  std::vector<std::string> mMsgVars;

  /**
   * A string containing further detailed information of the current state of the optimization method (optional).
   */
  std::string mStatusDump;

private:

  // Operations
private:

protected:
  /**
   * Replace %s%, %_timestamp% and %_iteration% in strings.
   * @param const std::string & string template
   * @param unsigned C_Int32 * offset in mMsgVars
   * @return std::string filledString
   */
  std::string fillString(const std::string & str, unsigned C_INT32 varOffset = 0) const;

  unsigned C_INT32 countVars(const std::string & str) const;

public:
  /**
   * Constructor.
   */
  COptLogItem(MsgID id, const std::string& statusDump = "");

  /**
   * Destructor
   */
  virtual ~COptLogItem();

  /**
   * Enter iteration value for this log item.
   * @param unsigned C_INT32 iteration
   * @return COptLogItem & logItem
   */
  COptLogItem & iter(size_t val);

  /**
   * Enter further values for this log item.
   * @param <T> value
   * @return COptLogItem & logItem
   */
  template <class T>
  COptLogItem & with(T arg)
  {
    assert(mMsgVars.size() < mVarCount);

    std::stringstream s;
    s << arg;
    mMsgVars.push_back(s.str());

    return *this;
  }

  MsgID getMsgId() const;

  time_t getTimestamp() const;

  std::string getHeader() const;

  std::string getSubtext() const;

  std::string getStatusDetails() const;
};

#endif  // COPASI_COptLogItem
