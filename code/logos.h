#pragma once

#include <iostream>
#include <string>

struct GameLogos {
    static constexpr const char* alpha = R"(

    ////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                        //
    //       █████                ███ ████         █████████   █████                          //
    //     ███░░░███            ███░ ░░███        ███░░░░░███ ░░███                           //
    //    ███   ░░███         ███░    ░███       ░███    ░░░  ███████    ██████  ████████     //
    //   ░███    ░███       ███░      ░███       ░░█████████ ░░░███░    ███░░███░░███░░███    //
    //   ░███    ░███     ███░        ░███        ░░░░░░░░███  ░███    ░███████  ░███ ░███    //
    //   ░░███   ███    ███░          ░███        ███    ░███  ░███ ███░███░░░   ░███ ░███    //
    //    ░░░█████░   ███░            █████      ░░█████████   ░░█████ ░░██████  ░███████     //
    //      ░░░░░░   ░░░             ░░░░░        ░░░░░░░░░     ░░░░░   ░░░░░░   ░███░░░      //
    //                                                                           ░███         //
    //                                                                           █████        //
    //                                                                          ░░░░░         //
    //                                                                                        //
    ////////////////////////////////////////////////////////////////////////////////////////////

    )";
    static constexpr const char* big = R"(

        █████████████████████████████████████████████████████
        █▌                                                 ▐█
        █▌              ,a8888a,             d8    88      ▐█
        █▌            ,8P"'  `"Y8,         ,8P'  ,d88      ▐█
        █▌           ,8P        Y8,       d8"  888888      ▐█
        █▌           88          88     ,8P'       88      ▐█
        █▌           88          88    d8"         88      ▐█
        █▌           `8b        d8'  ,8P'          88      ▐█
        █▌            `8ba,  ,ad8'  d8"            88      ▐█
        █▌    ad88888ba "Y8888P"   8P'             88      ▐█
        █▌   d8"     "8b  ,d                               ▐█
        █▌   Y8,          88                               ▐█
        █▌   `Y8aaaaa,  MM88MMM  ,adPPYba,  8b,dPPYba,     ▐█
        █▌     `"""""8b,  88    a8P_____88  88P'    "8a    ▐█
        █▌           `8b  88    8PP"""""""  88       d8    ▐█
        █▌   Y8a     a8P  88,   "8b,   ,aa  88b,   ,a8"    ▐█
        █▌    "Y88888P"   "Y888  `"Ybbd8"'  88`YbbdP"'     ▐█
        █▌                                  88             ▐█
        █▌                                  88             ▐█
        █▌                                                 ▐█
        █████████████████████████████████████████████████████

    )";
    static constexpr const char* base = R"(

    +====================================================================================+
    |                                                                                    |
    |         :::::::       :::  :::         :::::::: ::::::::::: :::::::::: :::::::::   |
    |       :+:   :+:     :+: :+:+:        :+:    :+:    :+:     :+:        :+:    :+:   |
    |      +:+   +:+    +:+    +:+        +:+           +:+     +:+        +:+    +:+    |
    |     +#+   +:+   +#+     +#+        +#++:++#++    +#+     +#++:++#   +#++:++#+      |
    |    +#+   +#+  +#+      +#+               +#+    +#+     +#+        +#+             |
    |   #+#   #+# #+#       #+#        #+#    #+#    #+#     #+#        #+#              |
    |   ####### ###      #######       ########     ###     ########## ###               |
    |                                                                                    |
    +====================================================================================+

    )";
    static constexpr const char* author1 = R"(
 l    EAA               AA      zz   g SO     Au   A                     zz z pz    pzbAzu u          pz               gA      z   zp                      
                          AO   p  u   p bE     Ab  bb               zzzzz zzuz lz      Al  l       p           buS    8u l  gzzu  u   u         8   bl     
             u z       z   ug8  zz u  zu A8  z  A   S              zzz         pz u    g b u       u   l        l  g Oz 8  p b z   uX      lSAAJ lzb zlp   
   lbp gz                    lpl    zz    bX u   A lu    zzz     u     z g     zl  zu l8 l                    lAl l Xz8    ubz     guzlz zp             up 
      p8JAAAAAAAAAAz      gpp   ulg  zzzz  up z3 gA 3p       uu  zzz   u 8      uz  z pg u  z                Sp    JpS    b     lSlp  l3                 g 
                  lA 3AAz          uzzuu u      u A 3   z      z  z   zz gu     u   u z  z   z                E  Alz3  z 8   Ap8   lA       pp             
           OgA3AAAu     u3AAA          z  zu z     AA p          z u   z 3g   u  zl  zz            u    zp  AO   3g   l   Ol    l      AAAAAu              
             XSpAAAAXAp      8AAX    z  z  uu      zA        z    z z    uX      zl  z                     AA   bp     pA  ppg    3AAAAA3A8 u              
           z         J Eb       zXAu         z     uEX        z    z zz  lX   A  zp z                z p  AA   uS    bAz uO    3AA8                        
                          zzuubb   uAA       z      b8          z  z  zz  AA  A  pl z                z    A    l   AS zAS  JAAAXO8         zp              
            plbOSbJAAAAE              XA             lu         u    z z  OA  A  zp                 ul   A       Au AAz  lXuElgb        u     glu          
         z  8XJE8z   gAAAAAAA   pb      lA   uz z    b       zz z         AOX AA 3z                  l  A      A  AA    llu     zAAAAAASAAAAEg z           
          8AAA              JAAAAA   A    3A    z    z z    z  zz zz      A gl  AAp                 z  Ag    A  AASzpAAA     AAA          uEAAblpuz        
     z       p   AAAA3         gblJAAp zJ   pu        p  z                A      A                    AS    A AAA  z    gAAA   b3               3          
     lg  l83SAS  8AAAAAAAAOp  zl      AA8 u   8  zzz       z      z      pS     pA                   Ag   O8AbA      AAAA XAAAz    JAAAAAAA     bgbu z     
    uz   u zgSA   AAEAAAgXJAAJ    AA    lAAu    l  zz zz z      z  z   z         A z                A3   AAg A    AAA3AAE       AAAAXXX3AAA    lSzlg8u upl 
    pglglSOAAAAA  8AAOOAEAAAbOAAA    AO    AA    l       z                       A z               S    Xl  g  AAA          EAAAJg p3AJAAA8   bAEJSbp gzlu 
    l  z   bEAAAS  AAOJEJAAAAAAAAA 3u pEAb   AA8      z   zz            8        O     z          u         AAAA      l3z XAAXlz XAAAAOASp    AAOSSEgbzul  
    b b8bb3XEAOAA  8AAAJJAESOEAAAA  g        u  AX  z               z            l                z       uAAX      bA    AAp88AAAAAAAAA    gAAAAOg ubg3b  
    p      b3AOSAA   AAAESJAAAOAAA8    AAA    gJ                                 lz u z                 gAAE     XAAAAz  bAAAAAAAAAAEAA    AAAJ z pX8      
       gOSbb8JJSOAA   AAAJXOJgJAAAA   AA3EAA3   AJXl                                z p              l3AAu    pAAJ8zSAA  AAAAAAAAAAAAS    AAAAA3pugp       
         pulp8ESSSAA    AAA3zzbgAAA8 AAAAlbSAAg    8Op                  zz         zu z             XEu    lXAOOJAAAAAA  AA    OAAAA    AAAAASllz          
         8883AAAAAAAA8    AAASAOSAAAOAAAgXJAXgAAu  X  z                z           zp           llubS    OAAbOAAAAAlEAAXAAA pOAAAAu    AAEAAOg  u          
        ulgO8X8gpuOSAAA     AAAAJEAAAAASAXAEAA3uAA   J   z             z       uz   u        p8lgbAAg  pAASAAAAEEAOSgOAJAASAAAAAE    JAAAAA8               
                 8ASSSAAA    z AAAO3zzlbAAAAAAAAASA O3JO  pl                   uz   z    u uAb838OA   EAAAAAAAAAAAAAAlXAAOSAAAA    8AAAAJbu                
           p  bAAOAEOSSOAAA    uAAAAAAAAAAAEOAAAAAAAAu  zuu88     g          zzu   z  z    EE ugXAA      gAAAAAAAAAAAAAAA8JAb    AAAAAOu                   
            bpbEAAEXAJSSSJAAAAA       uu38XJAAAAAA        E S    p    z        p   zz  g3XXAl3JAAJ AA          3J3J83  AAE     gAAAAAAOu u8                
             u    gEOAESSSSSOOAAAAAAzbpAAAg3l      AAAAXp 33l b  b    z   zz zzz         pJO uJEu    3EAAb            8p bAAAAAAAAA8   u                   
                 X88OAAAAAEOSSSSSJSEAAO8lb3XJAAAAAAAAXSl Jb  zJpXzp   z      zz zz  8 p J  AA pAXbA3AAAAAAAAAAA3AAAAAEJJJJSSEAAAg 83u            zz    OSz 
                        zEAAAAAEOSSSSSSSSSSSSOAAAAAbz  z     g8 b bu  z  uz zuzzp    8 SuA  AzAb bA3AJOXSSSSSSOAAA3EAAOOAAAAAA3ASl            zu      z8   
  bb                zz lz   zSAAAAAAAAAAAAAAAAA3p  u zz zp   plpJJl pzzzuz z zz u  8  838uAAAAA uSO8ESAAAJSSSSSOOJAAAAAAAS   z     zz            z  g3zlz  
    8Az                   b3z  pXAJO8gg3bgg        z          u8ggll        uzu ug JAA  3 AASAJ lXggbSg3OAAAJEAXgAA3            z                 zXpu     
   z  XO8                    8bp    zp      ulzupuuz         zlu3b    zlg lz     3  gAA   XAAA   ul  uz z zAAAA p  pXz plu3uggpgp        zu   glu l        
    OAXp  z                               z z  z zp           z   pz zpuzzzzp z pu   gEAEX  AJ  zpg  uz u     b   pz     zz                 pgz l          
       OO    p8JJlgb8bpz       pgb8ggpu     z  zuppl                puu uzz p   8pu   zlAXEEA   plll l8p lpu   ullug3bbuupbl              zzu zz           
        zOAg           z3EAO3bgu     uzzu up   uuu            z   gup  z    ubulAl       AAAA   uzbll lbz  zluulggu                      ul                
          z3AAJAAS3g          z  zzz   gbblgzblzu                 p puzu zOl        g  EA SAA   lzgplzuplgbOEOl                        Eu  lE        zz    
                    zpS8l         z        ulgulbbu   p           p lXu ll8  lXXlz  JAAAAAAAl    z8puuupu3z                     z      3 p pb83            
            zupb3E8uu z  lpuz  pglglpzzpl                         l  ulzl uzAu  z  bAAAJOSSA      pbppplp8                   uz  zzgEbu               z3p  
 SX8lz                            ugX8l z bp                      pz ul lzuz  lz uA8JAAAOJOA       Ou z                    u   uuu         gAAAAA          
                      z   z u         zlp    z                     pz lzu  uu u8Xz  g  ASJJA        3gz zg  zz          zuzz       JAAbg z                 
                             u           3b                         z gluzzupzl       pAAAAA        zgS 8  zzz z            zAAAAX         zu              
 zl8S     833gbEp uu  EAAA3g                lb                      u  glplluupp   u  AAAAAA ll lu    g uz     z        SAAA         pu8A8                 
                 z    S3lp 3u uAAAA                      uz         zuu XXggp  u8zul  A     Ou     zz   z           8AAu      zulb8pu                      
                u3SS              uEAAAAA                   z               8glggl   AO   u S u838   u          lE3        uppuz                           
           ulgu             p  u8b       8AAA               z          z           z OX pA    AAl        z zpO3           g3zgz                            
       zp              zuuz                   uuz           u                 z  z l  3 lAzl  Xgp        zuz zuuu pXz   u          zJA3                    
                                                                                  zu zA 833 ggAl                    up   AJ                                
                         z3JAAAAAAAAO8bl                                             Xl p Agl3p  u            zSEAAEX  88      ulllpulSX                   
   3OEb              bJ8l                 u                                         8    AAO 3              lbp      uAp     u8AAAAS                       
                                   lX3Xlzzz zp                                       OAAJugJ A              g8XSSEAAA      uO             XAz              
                          uEAAAAXu                           bOu                    AAAp   bA  z  z    u8Sl    gbS     uu       AA             pp          
                     zAAAl                  l8u               OXb    uz           AOAzglSAAA     z z zz     EJAAA          Xz      zAA             pz  S   
                 JOSXz                  38                      OEgz       zAAAAb p     A3       zz      u3AAAA      Az       zA       bAJ                 
            lEX                zz    XA   zb3z                      uu               z                gEAAO   u3pAz    AA        bA        Sl              
  p     lJl                  z    pA        z8bl                        XA       SA         z     EAAAAASg      A  AX    AA         AA       ul            
      8                         Ab              zz                        AAAAAAAA             uAAAA         A   OE zA     AA          A        g          
  b3                        pAA                                              E             uAAAA              AA  OA  Ap     lA          O        lg       
                          AEu                           zu                              XAAAz   8               A   A  AA A   p A          p         S     
                       AA                                   AAAu      uAAAAAAAAAAAAAAAAAb       z                A   A  3b  A     A          z         A   
                     A                                             g8gz  AS                                       A   A  bO  lA                          3 
                   A                                                   AX              A                 p         A   Ab g    SX                          
                 O                                                    8                 l                               8  p     O                z        
               3                                                                        b                                A        lu                E      
                                                                                                                          J         l                 z    
           p                                                                                                               A                           z   
         pz                                                                                                                 A                              
        S                                                                                                                    A                             
    )";
    static constexpr const char* author2 = R"(
                                                                                                                                                           
                                         :.         ...   .    Xx:;+;      .                              :+X$$$$x;.
                                          ;::.        .         ;x...       .                          :++;:     
                                           :;;;;;.     .:: .      :                                 .:.       .:;+;:..
                                               :;;+:  .:;++:                                      .        . .::. 
                                     ..:        .:;+;:.  ..;;.
                                       ..          :;.:.    ;:..                                       ..::;;;;;;;;:
                                                     :..:.     .                                           .:;++++++x+;:...   .           .
                                       .                                                                              ..::;::  ... 
                                                 ..                                              .:.  ....:.
                                                  .::;+;;.:..                                 :.. .:++x++;:::;;;::::..
                                                 ...:.:;;;++x+;:                                            .:;++;+:;:::+++:::.
                                               ..::::;:::.:.:;x+xX+:
                                              ..:.:;:;;;::;;;:+:;++X&$:                                           ...
                                              ...::::...;:;;::;;::.:;+X&&+.      .+$$&&&&&&&&&&&&&&&&&&&$;         :+X&&&$x;;:: .
                                              .::;;:;;+++:;++;;;++xxxxxxX$&&&&&&&&&&$$$XxxxxXxxxxxxxxxx+x$&&$:        :X&&&+::.
                                            ...::.::+::::+;;:++++;;;;+;;+xxxxXXxXxXXxXxxXXxxx++++++xx+xxx+++x&&X      ..
                                             .::;;:::;+;;;;;++x+;;xxx+xxxx+xxXXXxxxxxxxxxxxxXXxXxXxxXxxx+x+++++$&:                                         
                                           ....:.:;::::;;;x++;;x+++xx+xx++x+xx++xxXXXXXXXXXxXx+XXx++xXXXxXXx+++++X.
                                           .::.::::::.;+++;+x+++++x++x+xxxxxxxxXXxXxXXxXxXXxXXXXXxXXXXxXxXxxxxxx++XX
                                          .....:::;+;;+;:+++;;++x+xxxxxxx+xxxXXXXXXXXXX$XxXXXxX$$X$XXX$XXXxXXXXxxx;x;            ..  
                                           .::;:;;:::;+;;+++;;+x++xx+++xxxxxXXXX++x+xXxxxXXXXX$XXXXX$$$$&$Xxxxxxx+++X     
                                            ....;;;;;;+;+++x+++x++x+++xxxxxx+xxXxx+xxxXXXXXXX$X$$$$$$$$$X$&X$XxxxX++++
                                             :::;::::;+:::;+++++;xx+xxxXxxxxxxxXXxxx$XXXXX$$$&&$$&$&&$&$&&&$$XXXXXxxx$        .            .
                                           .:.::;::;:;;;;++++;xx++++xxx++xxxxxxxxXXXXXX$$XX$X$XXX$$$X&&$$$$$&&$$$XxxxX+          .   
                                         ..::::;;:;;;;;+x+;+;;+xx+x+++x++xxxXXxxXXXxXXXXXxxxxxXXX$&&&&&&&&&&&&&$$$xxxX:             ...
                                           .::;:::;:;;+;;+;+++xx++xxx+XXxxx+X$X$XXX$$$X$XXXXXX$XX$&&&$&$&&&$$&&&$XXXx$                  .:
                                        ..:::::.:.;:;;++;++++xx+x$xx+++xx++xxXxXxXXXxXXx+xxxxxxXX$$&&&$&&&&&&&&&&$XxxX
                                        .:;::;;;::+;+++++xXxxxx++x++Xx+;xxxxXXXXxXX$$$X$$$$$$&&&$&&&$&&&&&&&$&&&&&$$$X
                                         :;;:+++++++++xXxxxxxXXxx+x++xXxx+$&&&&&&&&&&&&$&X$&&&&&&&&&&&&&$$&$$$$&&&$$Xx   .
                                       .:+X&&&&&&&&&&&&&&&&&&&&&&xxxx+xxxx&$.;.;&&&&&&&&&&&&&&&$$$$$$$$$$&&&&&&&&&&&x. . 
                                       ;X&$                      XXxx+x++xX              ;X&&&&&&&&&&&&&&&&&&&&$&&&&; :: 
                                      ::                         &$XxxxX+X&+.                  :&&&&&&&&&&&&&&&&$&&$  :
                                     .:                      $$X&&XxxxXx+xX&&&&&&&&&&&$:         :&&&&&$&&&&&&&&&&&+   ..
                                           :$&&&&&&&&&&&&&&&&&&&Xxx++x++;;;;++xX$&&&&&&&&&&&&X      &&&&&&&&&&&&&&&:            .  
                                       :X&&$Xx++x++++;;;+x;+;;++++xx+Xx+;;;++xx+++++;;;+xxX$&&&&x    &&&&&&&&&&&&&x            ;:   
                             ;        x&&x+;;:.....;;;;:::;;:+;x+++;+Xx+;++++++xxxxx++xx++++;+X&&&;  ;&&&&&&&&&&&&:           .+.
                            +.       .               .::;:;::;:+;:+;$$x+;++;;;++++;+++;;xxxx+;+x&&&+  &&&&&&&&&&&&            ;;
                           X.   :x.  +X$$X$X$&&&&&&x.   .:;:::;:;:::Xx+x;++x++;+++++++++;;;+xxx++X&&X &&&&&&&&&&&$
                          X   +      xxxxx++;:.;;+x+x+:    :.;;:::+X$Xxx;;:::;;;;+++;;;+++;++++x+X&&&++&&&&&&&&&&x
                          . +x      ;Xxx+;;;;;;;;:;;;++;.    .:;  +X$xxx++;++x++::;;:;+++x+xxx++X$&&&XX&&&&&&&&&&
                            :       X&&XXXx+x&&&&&$Xxx$Xx:.       X$x+;;++xx;..:.;++;;.  :;+XXX++xX&&&&&&&&&&&&&+
                       .    $       +             &&&$XxXx +     :&$+++xx:  :;;xX&&&&&&&&&x;  +$&$x&&&&&&&&&&&&&:
                       .    +       : X+&&&&&$ ;     &  ;$:;     :&X;;;. :x+;+:;..:..:;++xX&&&;  X&&&&&&&&&&&&&&
                            ;      .   &&&&&&&+&           ;    .X&+:;..Xx;:;;:;++++xXXxxXXXX$X&&  $&&&&&&&&&&&;
                            $      +:   ;&&&&&  .;   $X && ;    ;&&++;.X;:;;.       +$&&&&&&&&$x$&&  &&&&&&&&&X ;X     $&&X
                       .     $    .+:x+.  .&&&&&  :$:  ;   X    +:  ;: +:+;   +&&&            &&&$&&x:&&&&&&&&+       .X; :&&
                       .     x   .;;;++++:     :$&$++X$&.   &&. &&XX: :xxX: x&&&&&$&+    && x   ;xx&& &&&&$;&X  :     .&&X.:&
                              .$  +;;+;xXXX$$x+;:+x$&$x;        &$X&X+:Xxx+. x&&&&x.$      ; &&.  ;&&. X;X&&&x     :: &&Xx+x&
                                ;;;:;++++xxXXxX$$$XXXx.. ;.    x&&+$Xx.xXxx;   +&&&. :;x;$x &&& XX$&&;&&&&&&&    .+;:X&&$x;$&
                                  +X;+x+xXXX$&&$$$X:   ;:+:    &&&+;;x;:$xx++;.   X&&$     X&  X&&&&& &&&&&&+  :x+.++&&&x++&&
                                  .;;+;;++:         :++;;;:   +$&$+xx$x ;XXxx++x+;..:X$&&&&XX&&&&&&&xX&&&&&&: ; ;.   X&&Xx$&
                                  .:.:+++x+xxxx$$X$XX+++;x:  .X+$xx++xxx:.XXXxxXX$&&&&&&&&&&&&$$&&&+ &&&&&&&  . .+;;.X&&xX&x
                                  .:.  :;;+++++x+++x++x;+x.  :X&&&x+++xxX; ;$$$X$X$$&&&&&&$&&$&&&& X&&&&&&&+    &&;.X&&$X&X
                                   .:::;::;++;+xx++xx$XX+   .+$&&&xXXxXX$&$:  +&&&&&&&&&&&&&&&&&  &&&&$$$$&$:$:$&& .&&$X&&
                                   .  .:.;:;;+;+xxx&X;      .+&&$&$$$&&$X$&&&&x   ;$&&&&&&&&:  &&&&&&&&&&&&&&&&&x .&&&&&& 
                                   . .. ::;::;;+x+x;      :++;xx$$X+$&$$$$XXXX&&&&&X;... :;+&&&&&&&$$$$&&&&&&X$$X&&&&&&&   
                                 ..+:..     .::;:;:     +;$X&&&&X$$x++&&&$$&$$$$X$&&&&&&&&&&$$&$&$$$&&&&&&&&&&&X$&&$&&+  
                                .:;xXxX+x; ..:;;;;;    :x;x+&&&&&&&&$+$&&$$$X$X$XXX$XXXXXxX$$$$&$&&&&&&&&&&&X$&&$$X&&+
                                 .:;xxX+++: :X+;:..:.   ;xXX$&&&&&&&x;x&$XXxxXxX$$$XxxxxX$$$&&$&&$$$$&&&$&&+;;+X$&&&+
                                 .:+++++:++   :Xx;.....    .:.       ;&&&$$$xxxxXXXX$X$XXxX$$&$&&&&&&&&&&&X ;xxX&&&$
                                  :x++;+;;;;:    x$&$++;:.    ;&&&&&&&&&&&&&$$$Xxxx+x+x+x+xXX$$$&&&&&&&&&&   xXX&&
                                   .;;++++;:+:      :$&&$&&&$&&&$&&&$$$$$$$$&&$X+;;+x+xxXXX&$&&&&$$$$$$&&&
                                   .;::;;;::;;:;  +&    :&&&&&&&&&&&&&&&&&&&&&&&X:.;xx$X$&&&$&&&$&&&&&&&&& 
                                   .;;;;;::::.;;:  &&&&&        ;X&$&&&&&&&&x+$&&&&&&&$$&&&&&&&$&$$&&$&&&
                                    .:;++;;;::.:;:    :&&&&&&&&&&+X&;       &&&&$&&$$&$$&&&&&&&&&&&&&&&&$
                                     .:;;;:... ..:...         ;$X      ;&&&&&&$$$$$$$$$$&$&&&&&&&&&&&&&&
                                       :;;;;;:..::;x+::             x&&&&&&&&&$&&&$$&&&&&&&&&&X$$$$&&&&
                                       ::;+;:;;;;:::+XX$&&&&&&&&&&&&&&&&&&&&&&&&&$$$&&&&&&&&$&&$$$&&&x
                                        .::++++;:..:;;;++xxX$$&&&&&&&&&&&&&$$&&&&&&$XXX$$&$&$&&&&&&&
                                         ..:+;++x+xxx+;+++xx+XxX$X&&$$$$$$$$$&&$$&&$$&&&$$$&$&&&&
                                           .:;+;++x+xXxxxx+x+XX$XXX$&&&XX$&$$$$$&&XX$&&&&&&&&&  
                                             .+;++xxxxxxX$XX$$&$X$$$$$$$$$$&&&&$$$&&&&$&&&&
                                              .+;++xx++XX$$$&&&&&&&&&&&$$$$$$&&$&$&&&&&X
                                              .XX+xxXXXXXXX$X&&&&&&&&&&&&&&&&&$x&&&.
                                               +x+xxxxXXXXX$$$&$$&&&&&&&&$x:  +&&
                                                x$X+++xx+xxXXxX$X$&&&&xx:;x&&&&$
                                                 +&$$Xxx++xxxxXXX$&$xxx$&&&&$
                                                    +X&&&$$XxxXxXXx$&&&&x.
                                                         .+XXX$&$X+
    )";
    static constexpr const char* extra1 = R"(

        ▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
        ▐                                                  ▌
        ▐                                                  ▌
        ▐       /$$$$$$                            /$$     ▌
        ▐      /$$__  $$                          | $$     ▌
        ▐     | $$  \__/  /$$$$$$   /$$$$$$   /$$$$$$$     ▌
        ▐     | $$ /$$$$ /$$__  $$ /$$__  $$ /$$__  $$     ▌
        ▐     | $$|_  $$| $$  \ $$| $$  \ $$| $$  | $$     ▌
        ▐     | $$  \ $$| $$  | $$| $$  | $$| $$  | $$     ▌
        ▐     |  $$$$$$/|  $$$$$$/|  $$$$$$/|  $$$$$$$     ▌
        ▐      \______/  \______/  \______/  \_______/     ▌
        ▐                                                  ▌
        ▐                                                  ▌
        ▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌

    )";
    static constexpr const char* extra2 = R"(

                ·····························
                :                           :
                :                           :
                :                  /$$$     :
                :                 /$$_/     :
                :      /$$       /$$/       :
                :     |__/      | $$        :
                :               | $$        :
                :      /$$      |  $$       :
                :     |__/       \  $$$     :
                :                 \___/     :
                :                           :
                :                           :
                ·····························

    )";
    static constexpr const char* thanks = R"(

    ▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
    ▐                                                                             ▌
    ▐                                                                             ▌
    ▐      ███████████ █████                           █████                      ▌
    ▐     ░█░░░███░░░█░░███                           ░░███                       ▌
    ▐     ░   ░███  ░  ░███████    ██████   ████████   ░███ █████  █████          ▌
    ▐         ░███     ░███░░███  ░░░░░███ ░░███░░███  ░███░░███  ███░░           ▌
    ▐         ░███     ░███ ░███   ███████  ░███ ░███  ░██████░  ░░█████          ▌
    ▐         ░███     ░███ ░███  ███░░███  ░███ ░███  ░███░░███  ░░░░███         ▌
    ▐         █████    ████ █████░░████████ ████ █████ ████ █████ ██████          ▌
    ▐        ░░░░░    ░░░░ ░░░░░  ░░░░░░░░ ░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░░           ▌
    ▐                        ██████                                               ▌
    ▐                       ███░░███                                              ▌
    ▐                      ░███ ░░░   ██████  ████████                            ▌
    ▐                     ███████    ███░░███░░███░░███                           ▌
    ▐                    ░░░███░    ░███ ░███ ░███ ░░░                            ▌
    ▐                      ░███     ░███ ░███ ░███                                ▌
    ▐                      █████    ░░██████  █████                               ▌
    ▐                     ░░░░░      ░░░░░░  ░░░░░                                ▌
    ▐                ████                        ███                      ███     ▌
    ▐               ░░███                       ░░░                      ░███     ▌
    ▐      ████████  ░███   ██████   █████ ████ ████  ████████    ███████░███     ▌
    ▐     ░░███░░███ ░███  ░░░░░███ ░░███ ░███ ░░███ ░░███░░███  ███░░███░███     ▌
    ▐      ░███ ░███ ░███   ███████  ░███ ░███  ░███  ░███ ░███ ░███ ░███░███     ▌
    ▐      ░███ ░███ ░███  ███░░███  ░███ ░███  ░███  ░███ ░███ ░███ ░███░░░      ▌
    ▐      ░███████  █████░░████████ ░░███████  █████ ████ █████░░███████ ███     ▌
    ▐      ░███░░░  ░░░░░  ░░░░░░░░   ░░░░░███ ░░░░░ ░░░░ ░░░░░  ░░░░░███░░░      ▌
    ▐      ░███                       ███ ░███                   ███ ░███         ▌
    ▐      █████                     ░░██████                   ░░██████          ▌
    ▐     ░░░░░                       ░░░░░░                     ░░░░░░           ▌
    ▐                                                                             ▌
    ▐                                                                             ▌
    ▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌

    )";
};