%{
    #include <string>

    extern "C" int yywrap() { return 1; }
%}

%%

[ \n\t]

"hello" printf("Hello\n");

%%
