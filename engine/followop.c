#include "followop.h"

#ifndef KERNEL_DS

UInt16 follow_straight (UInt16 where)
{
  UChar op = get_8bit_addr (where);

  return where + addr_info_debug[optable_debug[op].addr_mode].size;
}

UInt16 follow_BBRi (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar test_char = get_8bit_addr (get_8bit_addr (where + 1));
  UChar nb_bit = op >> 4;
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  test_char >>= nb_bit;

  if (!(test_char & 0x1))	// no jump
    return where + size;

  // jump
  return where + addr_info_debug[optable_debug[op].addr_mode].size
    + (SChar) get_8bit_addr (where + size - 1);

}

UInt16 follow_BCC (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (M.P & C_FLAG)		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BBSi (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar test_char = get_8bit_addr (get_8bit_addr (where + 1));
  UChar nb_bit = op >> 4;
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  test_char >>= nb_bit;

  if ((test_char & 0x1))	// no jump
    return where + size;

  // jump
  return where + addr_info_debug[optable_debug[op].addr_mode].size
    + (SChar) get_8bit_addr (where + size - 1);

}

UInt16 follow_BCS (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(M.P & C_FLAG))		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BEQ (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (M.ZF)			// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BNE (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(M.ZF))			// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BMI (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (M.NF & N_FLAG)		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BPL (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(M.NF & N_FLAG))		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BRA (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  return where + size		// always jump
    + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BSR (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (running_mode == STEPPING)	// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BVC (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (M.VF & V_FLAG)		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_BVS (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(M.VF & V_FLAG))		// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr (where + size - 1);
}

UInt16 follow_JMPabs (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  return get_8bit_addr (where + size - 2) + 256 * get_8bit_addr (where + size - 1);

}

UInt16 follow_JMPindir (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  UInt16 indir = get_8bit_addr (where + size - 2) + 256 * get_8bit_addr (where + size - 1);

  return get_8bit_addr (indir) + 256 * get_8bit_addr (indir + 1);

}

UInt16 follow_JMPindirX (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  UInt16 indir = get_8bit_addr (where + size - 2) + 256 * get_8bit_addr (where + size - 1);

  indir += M.X;

  return get_8bit_addr (indir) + 256 * get_8bit_addr (indir + 1);

}

UInt16 follow_JSR (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (running_mode == STEPPING)
    return where + size;	// no jump

  return get_8bit_addr (where + size - 2) + 256 * get_8bit_addr (where + size - 1);

}

UInt16 follow_RTI (UInt16 where)
{
  return RAM[SP + M.S + 2] + 256 * RAM[SP + M.S + 3];
}

UInt16 follow_RTS (UInt16 where)
{
  return RAM[SP + M.S + 1] + 256 * RAM[SP + M.S + 2] + 1;
}

#else

UInt16 follow_straight (UInt16 where)
{
  UChar op = get_8bit_addr (where);

  return where + addr_info_debug[optable_debug[op].addr_mode].size;
}

UInt16 follow_BBRi (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar test_char = get_8bit_addr (get_8bit_addr ((UInt16)(where + 1)));
  UChar nb_bit = op >> 4;
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  test_char >>= nb_bit;

  if (!(test_char & 0x1))	// no jump
    return where + size;

  // jump
  return where + addr_info_debug[optable_debug[op].addr_mode].size
    + (SChar) get_8bit_addr ((UInt16)(where + size - 1));

}

UInt16 follow_BCC (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (reg_p & FL_C)             // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BBSi (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar test_char = get_8bit_addr (get_8bit_addr ((UInt16)(where + 1)));
  UChar nb_bit = op >> 4;
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  test_char >>= nb_bit;

  if ((test_char & 0x1))	// no jump
    return where + size;

  // jump
  return where + addr_info_debug[optable_debug[op].addr_mode].size
    + (SChar) get_8bit_addr ((UInt16)(where + size - 1));

}

UInt16 follow_BCS (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(reg_p & FL_C))          // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BEQ (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (reg_pc & FL_Z)                     // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BNE (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(reg_pc & FL_Z))                  // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BMI (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (reg_p & FL_N)            // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BPL (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(reg_p & FL_N))         // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BRA (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  return where + size		// always jump
    + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BSR (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (running_mode == STEPPING)	// no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BVC (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (reg_p & FL_V)            // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_BVS (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (!(reg_p & FL_V))         // no jump
    return where + size;

  // jump
  return where + size + (SChar) get_8bit_addr ((UInt16)(where + size - 1));
}

UInt16 follow_JMPabs (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  return (UInt16)(get_8bit_addr ((UInt16)(where + size - 2)) + 256 * get_8bit_addr ((UInt16)(where + size - 1)));

}

UInt16 follow_JMPindir (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  UInt16 indir = (UInt16)(get_8bit_addr ((UInt16)(where + size - 2)) + 256 * get_8bit_addr ((UInt16)(where + size - 1)));

  return (UInt16)(get_8bit_addr ((UInt16)indir) + 256 * get_8bit_addr ((UInt16)(indir + 1)));

}

UInt16 follow_JMPindirX (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  UInt16 indir = (UInt16)(get_8bit_addr ((UInt16)(where + size - 2)) + 256 * get_8bit_addr ((UInt16)(where + size - 1)));

  indir += reg_x;

  return (UInt16)(get_8bit_addr ((UInt16)indir) + 256 * get_8bit_addr ((UInt16)(indir + 1)));

}

UInt16 follow_JSR (UInt16 where)
{
  UChar op = get_8bit_addr (where);
  UChar size = addr_info_debug[optable_debug[op].addr_mode].size;

  if (running_mode == STEPPING)
    return where + size;	// no jump

  return (UInt16)(get_8bit_addr ((UInt16)(where + size - 2)) + 256 * get_8bit_addr ((UInt16)(where + size - 1)));

}

UInt16 follow_RTI (UInt16 where)
{
  return (UInt16)(sp_base[reg_s + 2] + 256 * sp_base[reg_s + 3]);
}

UInt16 follow_RTS (UInt16 where)
{
  return (UInt16)(sp_base[reg_s + 1] + 256 * sp_base[reg_s + 2] + 1);
}


#endif
