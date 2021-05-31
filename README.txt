
Number of suppressed lines, suppressed chunks, average chunks size:
.                             : 6354 466  13
    lib                       :  255  16  15
        misc                  :  255  16  15
            scoped-map.hh     :   65   2  32
            scoped-map.hxx    :  152   1 152
            singleton.hh      :   16   1  16
            symbol.hxx        :    6   4   1
            test-symbol.cc    :    1   1   1
            unique.hxx        :    8   5   1
            variant.hh        :    6   1   6
            variant.hxx       :    1   1   1
    src                       : 6099 450  13
        ast                   : 1404  70  20
            array-exp.cc      :   20   1  20
            array-exp.hh      :   42   1  42
            array-exp.hxx     :   34   1  34
            assign-exp.cc     :   15   1  15
            assign-exp.hh     :   36   1  36
            assign-exp.hxx    :   23   1  23
            break-exp.cc      :    7   1   7
            break-exp.hh      :   29   1  29
            break-exp.hxx     :   12   1  12
            call-exp.cc       :   17   1  17
            call-exp.hh       :   44   1  44
            call-exp.hxx      :   34   1  34
            default-visitor.hxx:   20  11   1
            escapable.cc      :    1   1   1
            escapable.hh      :   30   1  30
            escapable.hxx     :   12   1  12
            field-var.cc      :   13   1  13
            field-var.hh      :   42   1  42
            field-var.hxx     :   34   1  34
            function-dec.hh   :    2   1   2
            if-exp.cc         :   20   1  20
            if-exp.hh         :   53   1  53
            if-exp.hxx        :   34   1  34
            let-exp.cc        :   15   1  15
            let-exp.hh        :   36   1  36
            let-exp.hxx       :   23   1  23
            method-call-exp.cc:   13   1  13
            method-call-exp.hh:   39   1  39
            method-call-exp.hxx:   23   1  23
            object-exp.cc     :    8   1   8
            object-exp.hh     :   29   1  29
            object-exp.hxx    :   12   1  12
            object-visitor.hxx:    9   5   1
            op-exp.cc         :   11   1  11
            pretty-printer.cc :  256   3  85
            pretty-printer.hh :   30   1  30
            record-exp.cc     :   18   1  18
            record-exp.hh     :   38   1  38
            record-exp.hxx    :   23   1  23
            record-ty.cc      :   14   1  14
            record-ty.hh      :   30   1  30
            record-ty.hxx     :   12   1  12
            seq-exp.cc        :   14   1  14
            seq-exp.hh        :   30   1  30
            seq-exp.hxx       :   12   1  12
            string-exp.cc     :    8   1   8
            string-exp.hh     :   29   1  29
            string-exp.hxx    :   12   1  12
            typable.cc        :    1   1   1
            typable.hh        :   30   1  30
            typable.hxx       :   11   1  11
            type-constructor.cc:    3   1   3
            type-constructor.hh:   30   1  30
            type-constructor.hxx:   11   1  11
        astclone              :   53  17   3
            cloner.cc         :   53  17   3
        bind                  :  398  24  16
            binder.cc         :  154   9  17
            binder.hh         :   37   3  12
            binder.hxx        :   49   3  16
            libbind.cc        :   14   1  14
            libbind.hh        :   15   1  15
            renamer.cc        :   19   1  19
            renamer.hh        :    6   2   3
            renamer.hxx       :   37   2  18
            tasks.cc          :   25   1  25
            tasks.hh          :   42   1  42
        callgraph             :    4   1   4
            call-graph-visitor.cc:    4   1   4
        canon                 :  263  17  15
            canon.cc          :   32   3  10
            exp-matcher.cc    :   10   4   2
            libcanon.cc       :   20   1  20
            stm-matcher.cc    :   21   4   5
            traces.cc         :  180   5  36
        combine               :  114   8  14
            binder.cc         :   29   1  29
            binder.hh         :   30   1  30
            libcombine.cc     :   11   3   3
            tasks.cc          :    4   1   4
            type-checker.cc   :   14   1  14
            type-checker.hh   :   26   1  26
        desugar               :  208   5  41
            bounds-checking-visitor.cc:  131   1 131
            bounds-checking-visitor.hh:    7   1   7
            desugar-visitor.cc:   69   2  34
            libdesugar.cc     :    1   1   1
        escapes               :   44   2  22
            escapes-visitor.cc:   31   1  31
            escapes-visitor.hh:   13   1  13
        inlining              :  163   4  40
            inliner.cc        :   76   1  76
            inliner.hh        :    1   1   1
            pruner.cc         :   77   1  77
            pruner.hh         :    9   1   9
        liveness              :  110   4  27
            flowgraph.hxx     :   32   2  16
            interference-graph.cc:   43   1  43
            liveness.cc       :   35   1  35
        llvmtranslate         :  251  42   5
            escapes-collector.cc:   39   8   4
            llvm-type-visitor.cc:    5   4   1
            translator.cc     :  207  30   6
        object                :  393  68   5
            binder.cc         :   34   3  11
            desugar-visitor.cc:  150  39   3
            libobject.cc      :    7   2   3
            libobject.hh      :    4   1   4
            renamer.cc        :   31   6   5
            tasks.cc          :    5   1   5
            tasks.hh          :    6   1   6
            type-checker.cc   :  156  15  10
        overload              :  133   4  33
            binder.cc         :   14   2   7
            type-checker.cc   :  108   1 108
            type-checker.hh   :   11   1  11
        parse                 :  466  26  17
            parsetiger.yy     :  426   7  60
            scantiger.ll      :   18   3   6
            tasks.cc          :    1   1   1
            tiger-driver.hxx  :   14  14   1
            tiger-parser.cc   :    7   1   7
        target                :  983  35  28
            arm               :  231   8  28
                arm-assembly.cc:    4   2   2
                arm-codegen.cc:  123   1 123
                arm-matcher.cc:   14   3   4
                runtime.s     :   90   2  45
            ia32              :  343   8  42
                gas-assembly.cc:    5   2   2
                gas-codegen.cc:  181   1 181
                gas-matcher.cc:   12   3   4
                runtime-gnu-linux.s:  145   2  72
            mips              :  409  19  21
                runtime.s     :  214   6  35
                spim-assembly.cc:   58   9   6
                spim-codegen.cc:  123   1 123
                spim-matcher.cc:   14   3   4
        temp                  :   54  16   3
            identifier.hxx    :   54  16   3
        translate             :  261  38   6
            exp.cc            :   34   6   5
            level.cc          :    3   1   3
            translation.cc    :  109  10  10
            translation.hh    :    9   1   9
            translator.cc     :  106  20   5
        tree                  :   43   1  43
            fragment.cc       :   43   1  43
        type                  :  754  68  11
            array.cc          :    7   1   7
            array.hh          :   23   1  23
            array.hxx         :    1   1   1
            attribute.hxx     :    1   1   1
            builtin-types.cc  :   23   1  23
            builtin-types.hh  :   74   1  74
            class.cc          :   40   6   6
            class.hh          :    1   1   1
            default-visitor.hxx:   11   5   2
            function.cc       :   26   1  26
            function.hh       :    1   1   1
            method.cc         :   10   1  10
            method.hh         :    1   1   1
            method.hxx        :    1   1   1
            named.cc          :   23   3   7
            named.hxx         :    2   1   2
            nil.cc            :    2   1   2
            pretty-printer.cc :   52   7   7
            record.cc         :   25   2  12
            record.hh         :    1   1   1
            type-checker.cc   :  396  21  18
            type-checker.hh   :   13   2   6
            type-checker.hxx  :   18   5   3
            type.hxx          :    2   2   1
