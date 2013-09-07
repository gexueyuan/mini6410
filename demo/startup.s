
    IMPORT      _main                    ; C entrypoint for Steppingstone loader.
	AREA |C$$code|, CODE, READONLY
	global		Start

Start
        b        _main

		DCB		"ABCDabcd"
        END

