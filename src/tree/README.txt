/Tree/
    /Exp/
        Const (int value)
        Name  (const temp::Label& label)
        Temp  (const temp::Temp& temp)
        Binop (Oper oper, rExp& left, rExp& right)
        Mem   (rExp& exp)
        Call  (rExp& func, std::vector<rExp>& args)
        Eseq  (rStm& stm, rExp& exp)

    /Stm/
        Move  (rExp& dst, rExp& src)
        Sxp   (rExp& exp)
        Jump  (rExp& exp)
        CJump (Relop relop, rExp& left, rExp& right,
               rName& iftrue, rName& iffalse)
        Seq   (std::vector<rTree>)
        Label (const temp::Label& label)
