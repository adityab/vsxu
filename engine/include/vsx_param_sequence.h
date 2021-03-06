/**
* Project: VSXu: Realtime visual programming language, music/audio visualizer, animation tool and much much more.
*
* @author Jonatan Wallmander, Robert Wenzel, Vovoid Media Technologies Copyright (C) 2003-2011
* @see The GNU Public License (GPL)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef VSX_PARAM_sequence_H
#define VSX_PARAM_sequence_H

//#include "vsxfst.h"

class vsx_param_sequence_item {
public:
  float accum_time; // the time on wich this row starts
  float total_length; // in seconds (float)
  vsx_string value;
  int interpolation;
  vsx_vector handle1;
  vsx_vector handle2;
  vsx_string get_value() {
    if (interpolation == 4) {
      return value+":"+f2s(handle1.x)+","+f2s(handle1.y)+":"+f2s(handle2.x)+","+f2s(handle2.y);
    } else {
      return value;
    }
  }

  vsx_param_sequence_item();
};

class vsx_param_sequence {
  float last_time; // last time we were called, to see if we should trace back
  float line_time; // current line time (accumulated)
  int line_cur; // current line
  vsx_string cur_val, to_val;
  float cur_delay;
  int cur_interpolation;
  float total_time;
public:
  //vsx_string param_name;
  //int param_type;
  void* engine;
  vsx_comp_abs* comp;
  vsx_engine_param* param;
  bool repeat; // repeat this or stop at end?

  //static float g_time; // system-wide time, only to be read.
  float time_scaler; // global multiplier

  float p_time; // internal time

  float interp_time; // interpolation time for use when feeding the engine interpolator

  std::vector<vsx_param_sequence_item> items; // the actual sequence

  //unsigned long row_pos; // current row position

  void set_time(float stime);
  void execute(float ptime); // returns command if available
  //void add_line(vsx_command_list* dest, vsx_command_s* cmd_in, vsx_string cmd_prefix = "");
  void update_line(vsx_command_list* dest, vsx_command_s* cmd_in, vsx_string cmd_prefix = "");
  void insert_line(vsx_command_list* dest, vsx_command_s* cmd_in, vsx_string cmd_prefix = "");
  void remove_line(vsx_command_list* dest, vsx_command_s* cmd_in, vsx_string cmd_prefix = "");
  void rescale_time(float start, float scale);
  float calculate_total_time(bool no_cache = false);
  vsx_string dump();
  void inject(vsx_string ij);
  vsx_param_sequence();
  vsx_param_sequence(int p_type,vsx_engine_param* param);
  // no copy constructor needed
};

#endif
