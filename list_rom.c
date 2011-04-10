#include "list_rom.h"
#include "utils.h"

#if defined(LINUX)
  #include "linux/limits.h"
#endif

#if defined(WIN32)
  #include "windef.h"
#endif

struct pce_rom_info *pce_romlist = NULL;
int pce_romlist_size = 0;

#if 0

ROM_TYPE ROM_LIST[NB_ROM] = {

// ROM NUMBER #0
  {0X8C4588E2,
   "1941 COUNTER ATTACK",
   "HUDSON",
   "HC91048",
   "08/23/91",
   "",
   "2p",
   JAP | SUPER_GRAPHX},

// ROM NUMBER #1
  {0X4C2126B0,
   "ALDYNES",
   "HUDSON",
   "HC91044",
   "02/22/91",
   "",
   "1p",
   JAP | SUPER_GRAPHX},

// ROM NUMBER #2
  {0XB486A8ED,
   "DAIMAKAIMURA",
   "CAPCOM",
   "NAPH-1008",
   "07/27/90",
   "",
   "1p",
   JAP | SUPER_GRAPHX},

// ROM NUMBER #3
  {0X3B13AF61,
   "BATTLE ACE",
   "HUDSON",
   "HC89026",
   "11/30/89",
   "",
   "",
   JAP | SUPER_GRAPHX},

// ROM NUMBER #4
  {0X1F041166,
   "GRANDZORT",
   "",
   "",
   "???",
   "",
   "",
   JAP | SUPER_GRAPHX},

// ROM NUMBER #5
  {0X0517DA65,
   "GRADIUS",
   "KONAMI",
   "KM91001",
   "11/15/91",
   "",
   "",
   JAP},

// ROM NUMBER #6
  {0X14FAD3BA,
   "PAC-LAND",
   "NAMCO",
   "",
   "???",
   "",
   "2p",

   },

// ROM NUMBER #7
  {0X1B5B1CB1,
   "DIE HARD",
   "NICHIBUTSU",
   "NB90003",
   "09/28/90",
   "",
   "",
   JAP},

// ROM NUMBER #8
  {0X25BE2B81,
   "AERO BLASTERS",
   "KANEKO",
   "TGX040051",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #9
  {0X1B2D0077,
   "TERRA CRESTA II",
   "NIHON BUSSAN",
   "NB96002",
   "11/27/92",
   "",
   "1p",
   JAP},

// ROM NUMBER #10
  {0XC356216B,
   "TAKIN IT TO THE HOOP",
   "AICOM",
   "",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #11
  {0X09A0BFCC,
   "S.C.I. - SPECIAL CRIMINAL INVESTIGATION",
   "TAITO",
   "TP03016",
   "01/25/91",
   "",
   "4p",
   USA},

// ROM NUMBER #12
  {0X2CB92290,
   "MR.HELI NO DAI BOUKEN",
   "IREM",
   "IC01002",
   "12/01/89",
   "",
   "aka MR.HELI's BIG ADVENTURE, 1p",
   JAP},

// ROM NUMBER #13
  {0X053A0F83,
   "DEEP BLUE",
   "PACK-IN-VIDEO",
   "",
   "???",
   "",
   "aka DEEP BLUE KAITEI SHINWA, 1p",

   },

// ROM NUMBER #14
  {0XD15CB6BB,
   "STREET FIGHTER II' CHAMPION EDITION",
   "CAPCOM",
   "HE93002",
   "06/12/93",
   "",
   "2p",
   JAP},

// ROM NUMBER #15
  {0X7632DB90,
   "P 47 THE FREEDOM FIGHTER",
   "AICOM",
   "AC89001",
   "03/20/89",
   "",
   "",
   JAP},

// ROM NUMBER #16
  {0X8DEF5AA1,
   "POWER TENNIS",
   "HUDSON",
   "HC93062",
   "06/25/93",
   "",
   "",
   JAP},

// ROM NUMBER #17
  {0XEECFA5FD,
   "DAVIS CUP TENNIS",
   "LORICIEL",
   "TGX040061",
   "???",
   "",
   "4p",
   USA},

// ROM NUMBER #18
  {0X560D2305,
   "FINAL MATCH TENNIS",
   "HUMAN",
   "HM91004",
   "03/01/91",
   "",
   "",
   JAP},

// ROM NUMBER #19
  {0X6B319457,
   "SPLATTERHOUSE",
   "NAMCO",
   "",
   "???",
   "",
   "1p",

   },

// ROM NUMBER #20
  {0X3219849C,
   "DRAGON SABER",
   "NAMCO",
   "NC91005",
   "12/27/91",
   "",
   "",
   JAP},

// ROM NUMBER #21
  {0X3F982D0F,
   "TURRICAN",
   "ACCOLADE",
   "ATGX04TUTG",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #22
  {0X25E0F6E9,
   "POWER DRIFT",
   "ASMIK",
   "AS02002",
   "04/13/90",
   "",
   "TGX020005",
   JAP},

// ROM NUMBER #23
  {0XE203F223,
   "OUT RUN",
   "SEGA",
   "NAPH-1016",
   "12/21/90",
   "",
   "",
   JAP},

// ROM NUMBER #24
  {0XDDC3E809,
   "THUNDER BLADE",
   "SEGA",
   "NAPH-1015",
   "12/07/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #25
  {0X64580427,
   "SPACE HARRIER",
   "NEC AVENUE",
   "H67G-1002",
   "12/09/88",
   "",
   "1p",
   JAP},

// ROM NUMBER #26
  {0X2DB4C1FD,
   "GHOST MANOR",
   "ICOM",
   "TGX040076",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #27
  {0X1C6FF459,
   "SPIN PAIR",
   "MEDIA RINGS",
   "MR90002",
   "12/14/90",
   "",
   "1p, linkable",
   JAP},

// ROM NUMBER #28
  {0XD8373DE6,
   "RABIO LEPIUS SPECIAL",
   "VIDEO SYSTEM",
   "VS-90003",
   "10/19/90",
   "",
   "",
   JAP},

// ROM NUMBER #29
  {0X03E28CFF,
   "VICTORY RUN",
   "HUDSON",
   "HC62003",
   "12/28/87",
   "",
   "1p",

   },

// ROM NUMBER #30
  {0X2CEE30EE,
   "CHAMPIONS FOREVER BOXING",
   "NEC",
   "TGX040077",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #31
  {0X4A3DF3CA,
   "BARUNBA",
   "NAMCO",
   "NC90003",
   "04/27/90",
   "",
   "",
   JAP},

// ROM NUMBER #32
  {0X6923D736,
   "SHANGHAI",
   "HUDSON",
   "HC62004",
   "10/30/87",
   "",
   "1p",
   JAP},

// ROM NUMBER #33
  {0X6C30F0AC,
   "15 IN 1 MEGA COLLECTION",
   "IMAGE",
   "",
   "???",
   "",
   "BOOTLEG",
   JAP},

// ROM NUMBER #34
  {0X637BA71D,
   "5 IN 1 FAMI COLLECTION",
   "IMAGE",
   "",
   "???",
   "",
   "BOOTLEG",
   JAP},

// ROM NUMBER #35
  {0X67AAB7A1,
   "ZIPANG",
   "PACK-IN-VIDEO",
   "PV-1005",
   "12/14/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #36
  {0X4A135429,
   "DARKWING DUCK",
   "DISNEY",
   "TGX040066",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #37
  {0X56739BC7,
   "DEAD MOON",
   "NATSUME",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #38
  {0X44E7DF53,
   "HATRIS",
   "BULLET PROOF",
   "MC91002",
   "05/24/91",
   "",
   "",
   JAP},

// ROM NUMBER #39
  {0XFF898F87,
   "OPERATION WOLF",
   "NEC AVENUE",
   "NAPH-1010",
   "08/31/90",
   "",
   "",
   JAP},

// ROM NUMBER #40
  {0XFAECCE20,
   "SALAMANDER",
   "KONAMI",
   "KM91002",
   "12/06/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #41
  {0XF8F85EEC,
   "XEVIOUS",
   "NAMCO",
   "NC90004",
   "06/29/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #42
  {0X0BE0E0A8,
   "DRAGON'S CURSE",
   "HUDSON",
   "TGX020039",
   "???",
   "",
   "aka ADVENTURE ISLAND, 1p",
   USA},

// ROM NUMBER #43
  {0XA5290DD0,
   "SPIRAL WAVE",
   "MEDIA RINGS",
   "MR91004",
   "12/13/91",
   "",
   "",
   JAP},

// ROM NUMBER #44
  {0X3AEA2F8F,
   "TRICKY",
   "IGS",
   "AI-03004",
   "07/06/91",
   "",
   "aka TRICKY KICK",
   JAP},

// ROM NUMBER #45
  {0X4D539C9F,
   "SKWEEK",
   "VICTOR",
   "JC63011",
   "08/02/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #46
  {0XE5E7B8B7,
   "HYPERDYNE SIDEARMS",
   "CAPCOM",
   "H54G-1004",
   "07/14/89",
   "",
   "",
   JAP},

// ROM NUMBER #47
  {0XC9D7426A,
   "BREAK IN",
   "NAXAT",
   "NX89002",
   "08/10/89",
   "",
   "4p",
   JAP},

// ROM NUMBER #48
  {0X67EC5EC4,
   "DROP ROCK HORA HORA",
   "DATA EAST",
   "DE90005",
   "03/30/90",
   "",
   "aka DROP OFF",
   JAP},

// ROM NUMBER #49
  {0X99496DB3,
   "SPACE INVADERS FUKKATSU NO HI",
   "TAITO",
   "TP02008",
   "03/02/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #50
  {0X99F7A572,
   "COLUMNS",
   "LASER SOFT",
   "TJ03002",
   "03/29/91",
   "",
   "1p, linkable",
   JAP},

// ROM NUMBER #51
  {0X67573BAC,
   "NINJA GAIDEN",
   "HUDSON",
   "HC92052",
   "01/24/92",
   "",
   "",
   JAP},

// ROM NUMBER #52
  {0X4F2844B0,
   "DELIVERY BOY",
   "TONKIN HOUSE",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #53
  {0X20EF87FD,
   "FORMATION ARMED F",
   "BIG DON",
   "PV-2004",
   "03/23/90",
   "",
   "",
   JAP},

// ROM NUMBER #54
  {0X8C565CB6,
   "ORDYNE",
   "NAMCO",
   "NC89004",
   "09/08/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #55
  {0XB24E6504,
   "YO' BRO",
   "ICOM",
   "TGX040054",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #56
  {0XB2EF558D,
   "LIQUID KIDS",
   "TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #57
  {0X740491C2,
   "PC DENJIN",
   "HUDSON",
   "HC92053",
   "11/20/92",
   "",
   "1p",
   JAP},

// ROM NUMBER #58
  {0XE3284BA7,
   "AIR ZONK",
   "HUDSON",
   "TGX040084",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #59
  {0XAF2DD2AF,
   "FINAL SOLDIER",
   "HUDSON",
   "HC91045",
   "07/05/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #60
  {0XD50FF730,
   "F1 DREAM",
   "NEC AVENUE",
   "H54G-1005",
   "08/25/89",
   "",
   "",
   JAP},

// ROM NUMBER #61
  {0XE14DEE08,
   "F1 CIRCUS",
   "NICHIBUTSU",
   "NB89002",
   "09/14/90",
   "",
   "",
   JAP},

// ROM NUMBER #62
  {0XD7CFD70F,
   "F1 CIRCUS '91",
   "NICHIBUTSU",
   "NB91004",
   "07/12/91",
   "",
   "",
   JAP},

// ROM NUMBER #63
  {0XB268F2A2,
   "F1 CIRCUS '92",
   "NICHIBUTSU",
   "",
   "06/14/05",
   "",
   "",
   JAP},

// ROM NUMBER #64
  {0XB4D29E3B,
   "CORYOON CHILD OF DRAGON",
   "NAXAT",
   "NX91004",
   "11/29/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #65
  {0X442405D5,
   "DRAGON EGG!",
   "MASYNYA",
   "NCS91003",
   "09/27/91",
   "",
   "",
   JAP},

// ROM NUMBER #66
  {0XBF3E2CC7,
   "HANI IN THE SKY",
   "FACE",
   "FA64-0001",
   "03/01/89",
   "",
   "",
   JAP},

// ROM NUMBER #67
  {0XE88987BB,
   "FIRE PRO WRESTLING: 2ND BOUT",
   "HUMAN",
   "HM91005",
   "08/30/91",
   "",
   "",
   JAP},

// ROM NUMBER #68
  {0X534E8808,
   "FIRE PRO WRESTLING 3: LEGEND BOUT",
   "HUMAN",
   "HM92006",
   "11/13/92",
   "",
   "",
   JAP},

// ROM NUMBER #69
  {0X03883EE8,
   "PSYCHO CHASER",
   "NAXAT",
   "NX90003",
   "04/06/90",
   "",
   "2p",
   JAP},

// ROM NUMBER #70
  {0X2DF97BD0,
   "CYBER COMBAT POLICE",
   "FACE",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #71
  {0XA594FAC0,
   "CYBER KNIGHT",
   "TONKIN HOUSE",
   "TON90003",
   "10/12/90",
   "",
   "",
   JAP},

// ROM NUMBER #72
  {0X56488B36,
   "SUPER METAL CRUSHER",
   "PACK-IN-VIDEO",
   "PV-1007",
   "11/29/91",
   "",
   "",
   JAP},

// ROM NUMBER #73
  {0X25A02BEE,
   "METAL STOKER",
   "FACE",
   "FA03-009",
   "07/12/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #74
  {0X92521F34,
   "IMPOSSAMOLE",
   "NEC",
   "TGX040062",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #75
  {0X647718F9,
   "PARODIUS",
   "KONAMI",
   "KM92003",
   "02/21/92",
   "",
   "",
   JAP},

// ROM NUMBER #76
  {0XAD450DFC,
   "HERO AGENT",
   "NEC HOME ELECTRONICS",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #77
  {0XC28B0D8A,
   "LEGEND OF HERO TONMA, THE",
   "IREM",
   "IC03005",
   "03/13/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #78
  {0XDF10C895,
   "KAISERS QUEST",
   "UPL",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #79
  {0XC6F764EC,
   "LADY SWORD",
   "GAMES EXPRESS",
   "T4955754200922",
   "???",
   "",
   "1p",
   JAP},

// ROM NUMBER #80
  {0X17BA3032,
   "DIGITAL CHAMP",
   "NAXAT",
   "NX89003",
   "10/13/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #81
  {0XF370B58E,
   "GUNBOAT",
   "NEC",
   "TGX040060",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #82
  {0X97C5EE9A,
   "TOY SHOP BOYS",
   "VICTOR",
   "JC63009",
   "12/14/90",
   "",
   "",
   JAP},

// ROM NUMBER #83
  {0XA15A1F37,
   "MARCHEN MAZE",
   "NAMCO",
   "NC90008",
   "12/11/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #84
  {0XA80C565F,
   "IMAGE FIGHT",
   "IREM",
   "IC02003",
   "07/27/90",
   "",
   "",
   JAP},

// ROM NUMBER #85
  {0XC614116C,
   "KNIGHT RIDER SPECIAL",
   "PACK-IN-VIDEO",
   "PV1003",
   "12/22/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #86
  {0X9107BCC8,
   "TIGER SHARK",
   "NEC AVENUE",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #87
  {0X29EEC024,
   "POWER SPORTS",
   "HUDSON",
   "HC92058",
   "10/10/92",
   "",
   "aka WORLD SPORTS COMPETITION, 5p",
   JAP},

// ROM NUMBER #88
  {0XF2E46D25,
   "MONSTER PRO WRESTLING",
   "ASK KODANSHA",
   "AK91002",
   "11/22/91",
   "",
   "",
   JAP},

// ROM NUMBER #89
  {0X965C95B3,
   "PUZZNIC",
   "TAITO",
   "TP02011",
   "06/29/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #90
  {0XA9AB2954,
   "WORLD JOCKEY",
   "NAMCO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #91
  {0XDA9A2DC9,
   "BATTLE ROYAL",
   "",
   "",
   "???",
   "",
   " USA",
   USA | US_ENCODED},

// ROM NUMBER #92
  {0X7424452E,
   "FALCON",
   "SPECTRUM HOLOBYTE",
   "TGX040067",
   "???",
   "",
   "1p, linkable",
   USA},

// ROM NUMBER #93
  {0X5CF59D80,
   "DETANA!! TWINBEE",
   "KONAMI",
   "KM92004",
   "02/28/92",
   "",
   "",
   JAP},

// ROM NUMBER #94
  {0XD20F382F,
   "TITAN",
   "TITUS",
   "NX91001",
   "03/15/91",
   "",
   "",
   JAP},

// ROM NUMBER #95
  {0XDD0EBF8C,
   "MAGICAL CHASE",
   "PALSOFT",
   "PL91001",
   "11/15/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #96
  {0XD7921DF2,
   "SON SON II",
   "NEC AVENUE",
   "H54G-1003",
   "01/27/89",
   "",
   "",
   JAP},

// ROM NUMBER #97
  {0XDD175EFD,
   "ATOMIC ROBOKID SPECIAL",
   "UPL",
   "UP01001",
   "01/19/90",
   "",
   "",
   JAP},

// ROM NUMBER #98
  {0XE415EA19,
   "NEW ADVENTURE ISLAND",
   "HUDSON",
   "TGX040080",
   "???",
   "",
   "1p",
   JAP},

// ROM NUMBER #99
  {0X1828D2E5,
   "FIGHTING RUN",
   "NICHIBUTSU",
   "NB91005",
   "11/29/91",
   "",
   "",
   JAP},

// ROM NUMBER #100
  {0X59D07314,
   "WONDER MOMO",
   "NAMCO",
   "NC64001",
   "04/21/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #101
  {0X0DF57C90,
   "BIO BOXER",
   "NAMCO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #102
  {0X8420B12B,
   "SOLDIER BLADE",
   "HUDSON",
   "HC92056",
   "07/10/92",
   "",
   "",
   JAP},

// ROM NUMBER #103
  {0XA9FAB7D2,
   "NIGHT CREATURES",
   "MANLEY & ASSOCIATES",
   "TGX040069",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #104
  {0XEDA32D95,
   "TALESPIN",
   "NEC",
   "TGX040056",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #105
  {0X727F4656,
   "STRATEGO",
   "ACCOLADE",
   "JC63012",
   "07/24/92",
   "",
   "",
   JAP},

// ROM NUMBER #106
  {0XCA72A828,
   "AFTER BURNER II",
   "SEGA",
   "NAPH-1011",
   "09/28/90",
   "",
   "",
   JAP},

// ROM NUMBER #107
  {0XCFEC1D6A,
   "TIME CRUISE",
   "FACE",
   "TGX040090",
   "???",
   "",
   "",
   USA | PINBALL_KEY},

// ROM NUMBER #108
  {0X013A747F,
   "DORAEMON NOBITA NO DORABIAN NIGHT",
   "HUDSON",
   "HC91051",
   "12/06/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #109
  {0XC0CB5ADD,
   "POCKY AND ROCKY",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #110
  {0X85101C20,
   "DOWNLOAD",
   "NEC AVENUE",
   "NAPH-1007",
   "06/22/90",
   "",
   "",
   JAP},

// ROM NUMBER #111
  {0XFFD92458,
   "BODY CONQUEST 2",
   "GAMES EXPRESS",
   "T4955754200953",
   "???",
   "",
   "1p",
   JAP},

// ROM NUMBER #112
  {0XB74EC562,
   "OVERRIDE",
   "DEKA",
   "DE90006",
   "01/08/91",
   "",
   "",
   JAP},

// ROM NUMBER #113
  {0XA3303978,
   "VALKYRIE NO DENSETSU",
   "NAMCO",
   "NC90006",
   "09/09/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #114
  {0XCA12AFBA,
   "TENSEIRYU SAINT DRAGON",
   "AICOM",
   "AC90001",
   "12/21/90",
   "",
   "1p",
   JAP | TWO_PART_ROM},

// ROM NUMBER #115
  {0XEEB6DD43,
   "DRAGON FIGHTER",
   "TONKIN HOUSE",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #116
  {0XC0AF0947,
   "VAMPIRE EMPEROR",
   "MASYNYA",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #117
  {0XB926C682,
   "GENPEI TORAMADEN",
   "NAMCO",
   "NC90001",
   "03/16/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #118
  {0X59E44F45,
   "BATTLE LODE RUNNER",
   "HUDSON",
   "HS93054",
   "02/10/93",
   "",
   "5p",
   JAP},

// ROM NUMBER #119
  {0XE6EE1468,
   "LODE RUNNER USHINA WARETA MAIKYUU",
   "PACK-IN-VIDEO",
   "PV1004",
   "07/27/90",
   "",
   "",
   JAP},

// ROM NUMBER #120
  {0X2B54CBA2,
   "APPARE! GATEBALL",
   "AZUMA",
   "HC63016",
   "12/22/88",
   "",
   "5p",
   JAP},

// ROM NUMBER #121
  {0XB3EEEA2E,
   "WORLD CIRCUIT",
   "NAMCO",
   "NC91004",
   "10/18/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #122
  {0X8F4D9F94,
   "BOUKEN DANSHAKAN DON SUNHEART HEN",
   "IMAX",
   "IM92001",
   "???",
   "",
   "aka THE LOST SUNHEART",
   JAP},

// ROM NUMBER #123
  {0X8E25DC77,
   "KIKI KAIKAI",
   "TAITO",
   "TP02009",
   "03/27/90",
   "",
   "",
   JAP},

// ROM NUMBER #124
  {0X9B5EBC58,
   "WINNING SHOT",
   "DATA EAST",
   "DE64001",
   "03/03/89",
   "",
   "4p",
   JAP},

// ROM NUMBER #125
  {0XBE8B6E3B,
   "POWER GATE",
   "PACK-IN-VIDEO",
   "PV-1008",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #126
  {0X3C33E016,
   "CART",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #127
  {0X57A436A2,
   "JACK NICKLAUS TURBO GOLF",
   "ACCOLADE",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #128
  {0X5C78FEE1,
   "MAISON IKKOKU",
   "FUJITV",
   "MC66680",
   "08/04/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #129
  {0X61A2935F,
   "RAISHISU",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #130
  {0X6C34AAEA,
   "MAHJONG SHIKAKA RETSUDEN MAHJONG WARS",
   "NICHIBUTSU",
   "NB1001",
   "02/01/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #131
  {0X6FD6827C,
   "GAIA NO MONSHO",
   "NCS",
   "NCS63001",
   "09/23/88",
   "",
   "",
   JAP},

// ROM NUMBER #132
  {0X91E6896F,
   "RYUKYU",
   "FACE",
   "",
   "10/26/90",
   "",
   "FA02-005, 1p",
   JAP},

// ROM NUMBER #133
  {0XA2A0776E,
   "WAI WAI MAHJONG",
   "VIDEO SYSTEM",
   "VS-89001",
   "06/19/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #134
  {0XB5326B16,
   "SUPER DODGE BALL",
   "TONKIN HOUSE",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #135
  {0XBA4D0DD4,
   "HANA TAHKA DAKA",
   "TAITO",
   "TP03018",
   "08/09/91",
   "",
   "",
   JAP},

// ROM NUMBER #136
  {0XC150637A,
   "JIMMU DENSHO YAKSA",
   "WOLF TEAM",
   "BG01003",
   "06/28/89",
   "",
   "",
   JAP},

// ROM NUMBER #137
  {0XC8C7D63E,
   "JYUOHKI",
   "SEGA",
   "HG8G-1006",
   "09/29/89",
   "",
   "aka ALTERED BEAST, 1p",
   JAP},

// ROM NUMBER #138
  {0XCC7D3EEB,
   "BONZE ADVENTURE",
   "TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #139
  {0XD4C5AF46,
   "MAKYO DENSETSU",
   "ATLUS",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #140
  {0XF131B706,
   "CRAZY JAPPY PLATFORMER",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #141
  {0X469A0FDF,
   "SHIRYOU SENSEN",
   "FUN PROJECT",
   "JC63002",
   "03/24/89",
   "",
   "aka WAR OF THE DEAD, 1p",
   JAP},

// ROM NUMBER #142
  {0X65FDB863,
   "NEKKETSU KOUKOU DODGEBALL BU PC BANGAI HEN",
   "TECHNOS",
   "NX90002",
   "03/30/90",
   "",
   "aka HOT BLOOD HIGHSCHOOL DODGEBALL",
   JAP},

// ROM NUMBER #143
  {0X53109AE6,
   "JASEIKIN NECROMANCER",
   "HUDSON",
   "HC62005",
   "01/22/88",
   "",
   "",
   JAP},

// ROM NUMBER #144
  {0X80C3F824,
   "YOUKAI DOCHUKI",
   "NAMCO",
   "NC62001",
   "???",
   "",
   "aka GHOST TRAVEL STORY",
   JAP},

// ROM NUMBER #145
  {0X34E089A9,
   "PRO YAKYUU WORLD STADIUM",
   "NAMCO",
   "NC63001",
   "05/20/88",
   "",
   "",
   JAP},

// ROM NUMBER #146
  {0XF70112E5,
   "TORIYUU SIYOUJIN NO JITSEN KABUSHIKI BAI BAI GAME",
   "INTEC",
   "IG89001",
   "11/01/89",
   "",
   "",
   JAP},

// ROM NUMBER #147
  {0X5CDB3F5B,
   "OUTLIVE",
   "SUNSOFT",
   "SS89001",
   "03/17/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #148
  {0XB122787B,
   "SENGOKU MAHJONG",
   "HUDSON",
   "HC63010",
   "07/08/88",
   "",
   "",
   JAP},

// ROM NUMBER #149
  {0XF022BE13,
   "TAKEDA SHINGEN",
   "AICOM",
   "AC89002",
   "07/28/89",
   "",
   "",
   JAP},

// ROM NUMBER #150
  {0XC0905CA9,
   "YUU YUU JINSEI",
   "TAKARA",
   "HC63008",
   "04/22/88",
   "",
   "aka VICTORY LIFE, 5p",
   JAP},

// ROM NUMBER #151
  {0XBE62EEF5,
   "MAKAI HAKKENDEN SHADA",
   "DATA EAST",
   "DE89002",
   "04/01/89",
   "",
   "",
   JAP},

// ROM NUMBER #152
  {0XF999356F,
   "SADAKICHI SABAN HIDEYOSHI NO OUGON",
   "HUDSON",
   "HC63014",
   "11/18/88",
   "",
   "",
   JAP},

// ROM NUMBER #153
  {0X1CAD4B7F,
   "USA PRO BASKETBALL",
   "AICOM",
   "AC89003",
   "12/01/89",
   "",
   "",
   USA},

// ROM NUMBER #154
  {0XA9084D6E,
   "KAIZOU NINGEN SHUBIBIMAN",
   "MASYNYA",
   "NCS89004",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #155
  {0X27A4D11A,
   "GANBARE! GOLF BOYS",
   "MASYNYA",
   "NCS89003",
   "03/28/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #156
  {0XEA751E82,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #157
  {0X8672717C,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #158
  {0X23EC8970,
   "SHOGI SHODAN ICCHOKUSEN",
   "HOMEDATA",
   "HD90001",
   "08/10/90",
   "",
   "",
   JAP},

// ROM NUMBER #159
  {0XE86249A4,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #160
  {0XC3212C24,
   "CIRCUS LIDO",
   "UNI POST",
   "PJ91001",
   "04/06/91",
   "",
   "",
   JAP},

// ROM NUMBER #161
  {0X457F2BC4,
   "SHOGI SHOSHINSA MUYO",
   "HOMEDATA",
   "HD91013",
   "11/29/91",
   "",
   "",
   JAP},

// ROM NUMBER #162
  {0XCAB21B2E,
   "CHIKUDENYA TOUBEE",
   "BIT2",
   "NX89004",
   "01/26/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #163
  {0XC7327632,
   "HISOU KIHEI SERD GAI SHADOW",
   "MASYNYA",
   "NCS90002",
   "02/23/90",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #164
  {0XF4148600,
   "MAHJONG GAKUEN MILD",
   "FACE",
   "FA02-004",
   "06/29/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #165
  {0XC42B6D76,
   "BENKEI GAIDEN",
   "SUNSOFT",
   "SS89002",
   "12/22/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #166
  {0X00F83029,
   "NO TITLE",
   "MASYNYA",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #167
  {0XDC47434B,
   "SINDIBAD CHITEI NO DAI MAKYU",
   "IGS",
   "AI-02002",
   "06/02/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #168
  {0XCF73D8FC,
   "SUSANO OH DENSETSU",
   "HUDSON",
   "HC89017",
   "04/27/89",
   "",
   "1p",
   USA},

// ROM NUMBER #169
  {0X99F2865C,
   "MANIAC PRO WRESTLING",
   "HUDSON",
   "HC89025",
   "05/25/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #170
  {0XFB0FDCFE,
   "NECROS NO YOUSAI",
   "ASK KODANSHA",
   "AK90001",
   "04/20/90",
   "",
   "",
   USA},

// ROM NUMBER #171
  {0XA71D70D0,
   "GAI FLAME",
   "MASYNYA",
   "NCS90001",
   "01/26/90",
   "",
   "",
   JAP},

// ROM NUMBER #172
  {0XF5B90D55,
   "MAHJONG GAKUEN TOUMA SHIRO TOJO",
   "FACE",
   "FA01-003",
   "11/24/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #173
  {0XCFC5A395,
   "JIGOKU MEGURI",
   "TAITO",
   "TP02013",
   "08/03/90",
   "",
   "aka TOUR OF HELL",
   JAP},

// ROM NUMBER #174
  {0X0038B5B5,
   "MAHJONG GOKU SPECIAL",
   "SUNSOFT",
   "SS90002",
   "08/10/90",
   "",
   "",
   JAP},

// ROM NUMBER #175
  {0X2E955051,
   "SEKIKEHARA",
   "TONKIN HOUSE",
   "TON90002",
   "09/14/90",
   "",
   "",
   JAP},

// ROM NUMBER #176
  {0XA326334A,
   "DAICHIKUN CRISIS DO NATURAL",
   "SALIO",
   "SL01001",
   "11/22/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #177
  {0XC2D2B823,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #178
  {0XFBA3A1A4,
   "NAXAT STADIUM",
   "TAISANG VERSION",
   "NX90006",
   "10/26/90",
   "",
   "",
   JAP},

// ROM NUMBER #179
  {0XA6539306,
   "KATTOBI! TAKUHAI-KUN",
   "TONKIN HOUSE",
   "TON90004",
   "11/09/90",
   "",
   "",
   JAP},

// ROM NUMBER #180
  {0X73593F61,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #181
  {0XE6C93AE7,
   "MAKAI PRINCE DORABO-CHAN",
   "NAXAT SOFT",
   "NX90007",
   "12/21/90",
   "",
   "",
   JAP},

// ROM NUMBER #182
  {0X4D3B0BC9,
   "OBOCCHAMA KUN",
   "NAMCO",
   "NC91001",
   "03/15/91",
   "",
   "",
   JAP},

// ROM NUMBER #183
  {0X82DEF9EE,
   "NIKO NIKO PUN",
   "KSS",
   "NV91001",
   "12/13/91",
   "",
   "",
   JAP},

// ROM NUMBER #184
  {0X9EC6FC6C,
   "IDOL HANAFUDA FAN CLUB",
   "GAMES EXPRESS",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #185
  {0X2546EFE0,
   "MORITA SHOGI PC",
   "RANDOM HOUSE",
   "NAPH-1021",
   "09/27/91",
   "",
   "",
   JAP},

// ROM NUMBER #186
  {0XA32430D5,
   "NHK TAIGA DRAMA TAIHEIKI",
   "NHK",
   "NV92001",
   "01/31/92",
   "",
   "",
   JAP},

// ROM NUMBER #187
  {0X951ED380,
   "CHIBI MARUKO-CHAN QUIZ DE PIHYARA",
   "NAMCO",
   "NC92001",
   "01/10/92",
   "",
   "1p",
   JAP},

// ROM NUMBER #188
  {0X4148FD7C,
   "PACHIOKUN JUBAN SHOBU",
   "COCONUTS",
   "CJ92002",
   "03/13/92",
   "",
   "",
   JAP},

// ROM NUMBER #189
  {0XF2285C6D,
   "NAXAT SOCCER",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #190
  {0X02DDE03E,
   "KIYUU KIYOKU MAHJONG IDOL GRAPHICS",
   "GAMES EXPRESS",
   "T4955754200915",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #191
  {0X4052FFAB,
   "UNKNOWN GAME",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #192
  {0XB01EE703,
   "HONO NO TATAKA TAMAKO DODGE DANPEI",
   "HUDSON",
   "HC92059",
   "09/25/92",
   "",
   "",
   JAP},

// ROM NUMBER #193
  {0X0AA88F33,
   "PC PACHISLOT IDOL GAMBLER",
   "GAMES EXPRESS",
   "T4955754200939",
   "???",
   "",
   "1p",
   JAP},

// ROM NUMBER #194
  {0XB866D282,
   "AV POKER WORLD GAMBLER",
   "GAMES EXPRESS",
   "T4955754200946",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #195
  {0XE5B6B3E5,
   "KIYUU KIYOKU MAHJONG IDOL GRAPHICS 2",
   "GAMES EXPRESS",
   "T4955754200977",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #196
  {0X85A1E7B6,
   "FORMATION SOCCER HUMAN CUP '90",
   "HUMAN",
   "HM90003",
   "04/27/90",
   "",
   "",
   JAP},

// ROM NUMBER #197
  {0X7146027C,
   "FORMATION SOCCER ON J.LEAGUE",
   "HUMAN",
   "HM94007",
   "01/15/94",
   "",
   "",
   JAP},

// ROM NUMBER #198
  {0XD5CE2D5F,
   "SUPER MOMO TAROU DENSETSU",
   "HUDSON",
   "HC89021",
   "09/15/89",
   "",
   "",
   JAP},

// ROM NUMBER #199
  {0X1555697E,
   "SUPER MOMO TAROU DENTETSU II",
   "SUMMER PROJECT",
   "HC91050",
   "12/20/91",
   "",
   "",
   JAP},

// ROM NUMBER #200
  {0X7B96317C,
   "MOMO TAROU DENSETSU TURBO",
   "HUDSON",
   "HC90034",
   "07/20/90",
   "",
   "",
   JAP},

// ROM NUMBER #201
  {0X345F43E9,
   "MOMO TAROU KATSU GEKI",
   "HUDSON",
   "HC90031",
   "09/21/90",
   "",
   "",
   JAP},

// ROM NUMBER #202
  {0XF860455C,
   "MOMO TAROU DENSETSU GAIDEN",
   "SUMMER PROJECT",
   "HC92060",
   "12/04/92",
   "",
   "",
   JAP},

// ROM NUMBER #203
  {0X6CCA614C,
   "MOMO TAROU DENTETSU II",
   "HUDSON",
   "HC90040",
   "12/22/90",
   "",
   "",
   JAP},

// ROM NUMBER #204
  {0X19FF94E5,
   "GOKURAKU CHUKA TAISEN",
   "TAITO",
   "TP03021",
   "03/13/92",
   "",
   "",
   JAP},

// ROM NUMBER #205
  {0XE749A22C,
   "GOKURAKU CHUKA TAISEN",
   "TAITO 384K STYLE",
   "TP03021",
   "03/13/92",
   "",
   "",
   JAP},

// ROM NUMBER #206
  {0XE87190F1,
   "MESOPOTAMIA",
   "ATLUS",
   "AT03001",
   "10/04/91",
   "",
   "aka SOMER ASSAULT, 1p",
   JAP},

// ROM NUMBER #207
  {0XF0227837,
   "SOMER ASSAULT",
   "ATLUS",
   "TGX040089",
   "???",
   "",
   "aka MESOPOTAMIA",
   USA},

// ROM NUMBER #208
  {0X767245CD,
   "CHINA WARRIOR",
   "HUDSON",
   "TGX020008",
   "???",
   "",
   "aka THE KUNG FU, 1p",
   USA},

// ROM NUMBER #209
  {0XDC268242,
   "CHINA WARRIOR",
   "NEC",
   "TGX020008",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #210
  {0XB552C906,
   "CHINA WARRIOR",
   "NEC",
   "TGX020008",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #211
  {0X5D0E3105,
   "SUPER STAR SOLDIER",
   "HUDSON",
   "HE-1097",
   "07/06/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #212
  {0XAB3C5804,
   "SUPER STAR SOLDIER",
   "HUDSON",
   "HE-1097",
   "07/06/90",
   "",
   "1p",
   USA},

// ROM NUMBER #213
  {0X82AE3B16,
   "TORA E NO MICHI",
   "CAPCOM",
   "JC63004",
   "02/23/90",
   "",
   "aka TIGER ROAD",
   JAP},

// ROM NUMBER #214
  {0XBF797067,
   "TORA E NO MICHI",
   "CAPCOM",
   "JC63004",
   "02/23/90",
   "",
   "aka TIGER ROAD",
   JAP},

// ROM NUMBER #215
  {0X9E86FFB0,
   "DOUBLE DUNGEONS",
   "MASYNYA",
   "NCS89006",
   "09/29/89",
   "",
   "2p",
   USA},

// ROM NUMBER #216
  {0X86087B39,
   "DOUBLE DUNGEONS",
   "MASYNYA",
   "NCS89006",
   "09/29/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #217
  {0XDB872A64,
   "KLAX",
   "TENGEN",
   "TTGX20001",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #218
  {0XC74FFBC9,
   "KLAX",
   "TENGEN",
   "TG90001",
   "08/10/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #219
  {0X8DC0D85F,
   "CADASH",
   "TAITO",
   "TP02015",
   "01/18/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #220
  {0X7D48D2FC,
   "CADASH",
   "TAITO",
   "TP02015",
   "01/18/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #221
  {0X9EDC0AEA,
   "CHAMPION WRESTLER",
   "TAITO",
   "TPO2014",
   "12/14/90",
   "",
   "",
   JAP},

// ROM NUMBER #222
  {0X76164593,
   "CHAMPION WRESTLER",
   "TAITO",
   "TP02014",
   "12/14/90",
   "",
   "",
   JAP},

// ROM NUMBER #223
  {0X69180984,
   "POWER LEAGUE BASEBALL",
   "",
   "",
   "???",
   "",
   " USA",

   },

// ROM NUMBER #224
  {0XD329CF9A,
   "POWER LEAGUE II",
   "HUDSON",
   "HC89020",
   "08/08/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #225
  {0XD3FD6971,
   "POWER LEAGUE III",
   "HUDSON",
   "HC90037",
   "08/10/90",
   "",
   "2p",
   JAP},

// ROM NUMBER #226
  {0X30CC3563,
   "POWER LEAGUE IV",
   "HUDSON",
   "HC91046",
   "08/09/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #227
  {0XBB654D1C,
   "POWER LEAGUE V",
   "HUDSON",
   "HC92057",
   "08/07/92",
   "",
   "2p",
   JAP},

// ROM NUMBER #228
  {0X66B167A9,
   "BASEBALL91",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #229
  {0X44F60137,
   "COLLEGE PRO BASEBALL '89",
   "INTEC",
   "IG89002",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #230
  {0X1772B229,
   "COLLEGE PRO BASEBALL '90",
   "INTEC",
   "IG90001",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #231
  {0X951AA310,
   "WORLD CLASS BASEBALL",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #232
  {0X9693D259,
   "BALLISTIX",
   "PSYGNOSYS",
   "CJ0001",
   "12/13/91",
   "",
   "2p",
   USA},

// ROM NUMBER #233
  {0X8ACFC8AA,
   "BALLISTIX",
   "PSYGNOSIS",
   "",
   "???",
   "",
   "2p",

   },

// ROM NUMBER #234
  {0X57615647,
   "SHOCKMAN",
   "NCS",
   "TGX040087",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #235
  {0X109BA474,
   "KAIZOU NINGEN SHUBIBIMAN 2",
   "MASYNYA",
   "NCS91001",
   "04/27/91",
   "",
   "aka SHOCKMAN, 2p",
   JAP},

// ROM NUMBER #236
  {0XCA68FF21,
   "ENERGY",
   "MASYNYA",
   "NCS89005",
   "04/19/89",
   "",
   "",
   JAP},

// ROM NUMBER #237
  {0XDD1D1035,
   "ENERGY",
   "MASYNYA",
   "NCS89005",
   "04/19/89",
   "",
   "",
   JAP},

// ROM NUMBER #238
  {0XA98D276A,
   "CYBER CORE",
   "IGS",
   "TGX030030",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #239
  {0XA0C97557,
   "CYBER CORE",
   "IGS",
   "AI-02001",
   "03/09/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #240
  {0XD0C250CA,
   "CYBER CROSS",
   "FACE",
   "FA01-002",
   "06/23/89",
   "",
   "",
   JAP},

// ROM NUMBER #241
  {0XDCD3E602,
   "CYBER CROSS",
   "FACE",
   "FA01-002",
   "06/23/89",
   "",
   "",
   JAP},

// ROM NUMBER #242
  {0X07BC34DC,
   "SAMURAI-GHOST",
   "NAMCO",
   "TGX040085",
   "???",
   "",
   "aka GENPEI TORAMADEN VOLUME 2, 1p",
   USA},

// ROM NUMBER #243
  {0X8793758C,
   "GENPEI TORAMADEN 2",
   "NAMCO",
   "NC92002",
   "04/07/92",
   "",
   "aka Samurai Ghost, 1p",
   JAP},

// ROM NUMBER #244
  {0X1EB30EEB,
   "FIRE PRO WRESTLING",
   "HUMAN",
   "HM89001",
   "06/22/89",
   "",
   "",
   JAP},

// ROM NUMBER #245
  {0X90ED6575,
   "FIRE PRO WRESTLING",
   "HUMAN",
   "HM89001",
   "06/22/89",
   "",
   "",
   JAP},

// ROM NUMBER #246
  {0XA17D4D7E,
   "GUNHED",
   "HUDSON",
   "HC89019",
   "07/07/89",
   "",
   "aka BLAZING LAZERS, 1p",
   JAP},

// ROM NUMBER #247
  {0X113DD5F0,
   "GUNHED",
   "HUDSON",
   "HC89019",
   "07/07/89",
   "",
   "aka BLAZING LAZERS, 1p",
   JAP},

// ROM NUMBER #248
  {0X7AA9D4DC,
   "BLAZING LAZERS",
   "HUDSON",
   "TGX030010",
   "???",
   "",
   "aka GUNHED, 1p",
   USA | US_ENCODED | TWO_PART_ROM},

// ROM NUMBER #249
  {0X3B3808BD,
   "TENNOKOE MEMORY BANK",
   "HUDSON",
   "",
   "???",
   "",
   "EXTRA SAVE RAM THING BY HUDSON",
   JAP},

// ROM NUMBER #250
  {0X51A12D90,
   "GAMES EXPRESS CD CARD 1993",
   "",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #251
  {0X3F9F95A4,
   "CD-ROM SYSTEM VER. 1.00",
   "NEC",
   "",
   "???",
   "",
   "56254:017",			// In bank 0xE1, address of the byte of replace and new value
   JAP | CD_SYSTEM},

// ROM NUMBER #252
  {0XD634D931,
   "CD-ROM SYSTEM VER. 2.00",
   "NEC",
   "",
   "???",
   "",
   "",
   USA | CD_SYSTEM},

// ROM NUMBER #253
  {0X283B74E0,
   "CD-ROM SYSTEM VER. 2.10",
   "NEC",
   "",
   "???",
   "",
   "51356:128",
   JAP | CD_SYSTEM},

// ROM NUMBER #254
  {0XDD35451D,
   "SUPER CD-ROM2 SYSTEM VER. 3.00",
   "NEC",
   "",
   "???",
   "",
   "51401:128",
   JAP | CD_SYSTEM},

// ROM NUMBER #255
  {0XE6F16616,
   "SUPER CD-ROM2 SYSTEM VER. 3.00",
   "NEC",
   "PCE-SC1",
   "???",
   "",
   "51401:128",
   JAP | CD_SYSTEM},

// ROM NUMBER #256
  {0XF42AA73E,
   "DON DOKO DON",
   "TAITO",
   "TP02010",
   "05/31/90",
   "",
   "2p",
   JAP},

// ROM NUMBER #257
  {0X633A3D48,
   "DON DOKO DON",
   "TAITO",
   "TP02010",
   "05/31/90",
   "",
   "2p",
   JAP},

// ROM NUMBER #258
  {0XBB761F3B,
   "HANI ON THE ROAD",
   "FACE",
   "FA02-006",
   "09/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #259
  {0X9897FA86,
   "HANI ON THE ROAD",
   "FACE",
   "FA02-006",
   "09/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #260
  {0X348022F7,
   "JJ & JEFF",
   "HUDSON",
   "TGX020014",
   "???",
   "",
   "aka KATO & KEN CHAN",
   USA},

// ROM NUMBER #261
  {0X6069C5E7,
   "KATO & KEN  CHAN",
   "HUDSON",
   "HC62006",
   "11/30/87",
   "",
   "aka JJ & JEFF",
   JAP},

// ROM NUMBER #262
  {0X88796264,
   "CHEW MAN FU",
   "HUDSON",
   "TGX020035",
   "???",
   "",
   "aka BE BALL, 2p",
   USA},

// ROM NUMBER #263
  {0XE439F299,
   "BE BALL",
   "HUDSON",
   "HC90028",
   "03/30/90",
   "",
   "aka CHEW-MAN-FU, 2p",
   JAP},

// ROM NUMBER #264
  {0X261F1013,
   "BE BALL",
   "HUDSON",
   "HC90028",
   "03/30/90",
   "",
   "aka CHEW-MAN-FU, 2p",
   JAP},

// ROM NUMBER #265
  {0X0B7F6E5F,
   "MOTO ROADER II",
   "MASYNYA",
   "NCS91002",
   "03/29/91",
   "",
   "5p",
   JAP},

// ROM NUMBER #266
  {0X364508DA,
   "MOTO ROADER II",
   "MASYNYA",
   "NCS91002",
   "03/29/91",
   "",
   "5p",
   JAP},

// ROM NUMBER #267
  {0X745408AE,
   "MOTO ROADER",
   "MASYNYA",
   "NCS89002",
   "02/23/89",
   "",
   "5p",
   JAP},

// ROM NUMBER #268
  {0X428F36CD,
   "MOTO ROADER",
   "MASYNYA",
   "NCS89002",
   "02/23/89",
   "",
   "5p",
   JAP},

// ROM NUMBER #269
  {0X13BF0409,
   "F1 TRIPLE BATTLE",
   "HUMAN",
   "HM89002",
   "12/23/89",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #270
  {0XB9DFC085,
   "F1 TRIPLE BATTLE",
   "HUMAN",
   "HM89002",
   "12/23/89",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #271
  {0X020DC2DF,
   "F1 PILOT",
   "PACK-IN-VIDEO",
   "PV1001",
   "03/23/89",
   "",
   "",
   JAP},

// ROM NUMBER #272
  {0X09048174,
   "F1 PILOT",
   "PACK-IN-VIDEO",
   "PV1001",
   "03/23/89",
   "",
   "",
   JAP},

// ROM NUMBER #273
  {0X3E647D8B,
   "POWER ELEVEN",
   "HUDSON",
   "HC91039",
   "06/21/91",
   "",
   "",
   JAP},

// ROM NUMBER #274
  {0X21B5409C,
   "POWER ELEVEN",
   "HUDSON",
   "HC91039",
   "06/21/91",
   "",
   "",
   JAP},

// ROM NUMBER #275
  {0X72E00BC4,
   "TOWER OF DRUAGA, THE",
   "NAMCO",
   "NC92003",
   "06/25/92",
   "",
   "",
   JAP},

// ROM NUMBER #276
  {0X8A046CDC,
   "TOWER OF DRUAGA, THE",
   "NAMCO",
   "NC92003",
   "06/25/92",
   "",
   "",
   JAP},

// ROM NUMBER #277
  {0XE8702D51,
   "PHOTOGRAPH BOY",
   "IREM",
   "IC04007",
   "10/02/92",
   "",
   "1p",
   JAP},

// ROM NUMBER #278
  {0XDFD4593A,
   "PHOTOGRAPH BOY",
   "IREM",
   "IC04007",
   "10/02/92",
   "",
   "1p",
   JAP},

// ROM NUMBER #279
  {0XC90971BA,
   "FINAL BLASTER",
   "NAMCO",
   "NC90007",
   "09/28/90",
   "",
   "",
   JAP},

// ROM NUMBER #280
  {0XB9899178,
   "FINAL BLASTER",
   "NAMCO",
   "NC90007",
   "09/28/90",
   "",
   "",
   JAP},

// ROM NUMBER #281
  {0XB18D102D,
   "ETERNAL CITY TOSHI TENSO KEIKAKU",
   "NAXAT",
   "NX91003",
   "04/12/91",
   "",
   "",
   JAP},

// ROM NUMBER #282
  {0X74903426,
   "ETERNAL CITY TOSHI TENSO KEIKAKU",
   "NAXAT",
   "NX91003",
   "04/12/91",
   "",
   "",
   JAP},

// ROM NUMBER #283
  {0XF91B055F,
   "CITY HUNTER",
   "SUNSOFT",
   "SS90001",
   "03/02/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #284
  {0XDF804DC7,
   "CITY HUNTER",
   "SUNSOFT",
   "SS90001",
   "03/02/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #285
  {0X44AF9BEA,
   "CRATERMAZE",
   "HUDSON",
   "TGX020027",
   "???",
   "",
   "aka DORAEMON MEIKYU DAISAKUSEN, 1p",
   USA},

// ROM NUMBER #286
  {0XDC760A07,
   "DORAEMON MEIKYU DAISAKUSEN",
   "HUDSON",
   "HC89023",
   "10/31/89",
   "",
   "aka CRATERMAZE, 1p",
   JAP},

// ROM NUMBER #287
  {0X04188C5C,
   "VEIGUES TACTICAL GLADIATOR",
   "VICTOR",
   "JC63005",
   "06/29/90",
   "",
   "3p",
   JAP},

// ROM NUMBER #288
  {0XF46298E3,
   "VEIGUES TACTICAL GLADIATOR",
   "VICTOR",
   "JC63005",
   "06/29/90",
   "",
   "3p",
   JAP},

// ROM NUMBER #289
  {0XAD6E0376,
   "VEIGUES TACTICAL GLADIATOR",
   "VICTOR",
   "",
   "???",
   "",
   "3p",
   USA},

// ROM NUMBER #290
  {0X96E0CD9D,
   "NINJA WARRIORS, THE",
   "TAITO",
   "TP01002",
   "06/30/89",
   "",
   "",
   JAP},

// ROM NUMBER #291
  {0X62654AD5,
   "NINJA WARRIORS, THE",
   "TAITO",
   "TPO1002",
   "06/30/89",
   "",
   "",
   JAP},

// ROM NUMBER #292
  {0X462256FB,
   "ROCK ON",
   "BIGCLUB",
   "BG01004",
   "08/22/89",
   "",
   "",
   JAP},

// ROM NUMBER #293
  {0X2FD65312,
   "ROCK ON",
   "BIGCLUB",
   "BG01004",
   "08/22/89",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #294
  {0XBE990010,
   "W RING THE DOUBLE RINGS",
   "NAXAT",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #295
  {0X83213ADE,
   "W RING THE DOUBLE RINGS",
   "NAXAT",
   "NX90005",
   "09/28/90",
   "",
   "",
   JAP},

// ROM NUMBER #296
  {0X1A8393C6,
   "GALAGA '88",
   "NAMCO",
   "NC63002",
   "07/15/88",
   "",
   "1p",
   JAP},

// ROM NUMBER #297
  {0X6273A9D4,
   "GALAGA '90",
   "NAMCO",
   "TGX020018",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #298
  {0XCE2E4F9F,
   "SUPER VOLLEY BALL",
   "VIDEO SYSTEM",
   "VS-90002",
   "02/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #299
  {0X09CBB5E6,
   "SUPER VOLLEY BALL",
   "VIDEO SYSTEM",
   "VS-90002",
   "02/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #300
  {0X23D22D63,
   "SONIC SPIKE",
   "IGS",
   "ITGX10001",
   "???",
   "",
   "aka WORLD BEACH VOLLEYBALL, 4p",
   USA},

// ROM NUMBER #301
  {0XBE850530,
   "WORLD BEACH VOLLEY",
   "IGS",
   "",
   "07/27/90",
   "",
   "aka SONIC SPIKE",
   JAP},

// ROM NUMBER #302
  {0XAD226F30,
   "VOLFIELD",
   "TAITO",
   "TP01005",
   "12/27/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #303
  {0X94C55627,
   "VOLFIED",
   "TAITO",
   "TP01005",
   "12/27/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #304
  {0X87FD22AD,
   "BOMBERMAN",
   "HUDSON",
   "HC90036",
   "12/07/90",
   "",
   "5p, linkable",

   },

// ROM NUMBER #305
  {0X9ABB4D1F,
   "BOMBERMAN",
   "HUDSON",
   "HC90036",
   "12/07/90",
   "",
   "5p, linkable",
   JAP},

// ROM NUMBER #306
  {0XB300C5D0,
   "BOMBERMAN '93",
   "HUDSON",
   "HC92061",
   "12/11/92",
   "",
   "5p, linkable",
   JAP},

// ROM NUMBER #307
  {0X05362516,
   "BOMBERMAN '94",
   "HUDSON",
   "HC93065",
   "12/10/93",
   "",
   "5p",
   JAP},

// ROM NUMBER #308
  {0X2CB5CD55,
   "PC GENJIN",
   "HUDSON",
   "HC89024",
   "12/15/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #309
  {0XB630AB25,
   "PC GENJIN",
   "HUDSON",
   "HC89024",
   "12/15/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #310
  {0X2CB796E2,
   "PC GENJIN",
   "HUDSON",
   "HC89024",
   "12/15/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #311
  {0X3028F7CA,
   "PC GENJIN 2",
   "HUDSON",
   "HC91043",
   "07/19/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #312
  {0XA170B60E,
   "PC GENJIN 3",
   "HUDSON",
   "HC93063",
   "04/02/93",
   "",
   "2p",
   JAP},

// ROM NUMBER #313
  {0XD5C782F2,
   "BONK'S ADVENTURE",
   "HUDSON",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #314
  {0X64301FF1,
   "BONK'S REVENGE",
   "HUDSON",
   "TGX040058",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #315
  {0X9913A9DE,
   "BONK 3 BONK'S BIG ADVENTURE",
   "HUDSON",
   "TGX080097",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #316
  {0XEB923DE5,
   "HEAVY UNIT",
   "TAITO",
   "TP01004",
   "12/22/89",
   "",
   "",
   JAP},

// ROM NUMBER #317
  {0XCAAD79CE,
   "HEAVY UNIT",
   "TAITO",
   "TP01004",
   "12/22/89",
   "",
   "",
   JAP},

// ROM NUMBER #318
  {0X60ECAE22,
   "NAXAT OPEN",
   "NAXAT",
   "NX89001",
   "05/30/89",
   "",
   "",
   JAP},

// ROM NUMBER #319
  {0X31DD1C32,
   "NAXAT OPEN",
   "NAXAT",
   "NX89001",
   "05/30/89",
   "",
   "",
   JAP},

// ROM NUMBER #320
  {0X2E5AC9C0,
   "BOXY BOY",
   "MEDIA RINGS",
   "TGX010031",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #321
  {0XFB37DDC4,
   "BOXY BOY",
   "MEDIA RINGS",
   "",
   "???",
   "",
   "aka SOHKO BAN WORLD",
   JAP},

// ROM NUMBER #322
  {0X2F8935AA,
   "MAJIN EIYU WATARU",
   "HUDSON",
   "HC63012",
   "08/30/88",
   "",
   "aka KEITH COURAGE IN ALPHA ZONES",
   JAP},

// ROM NUMBER #323
  {0XB54DEBD1,
   "KEITH COURAGE IN ALPHA ZONES",
   "SUNRISE",
   "TGX020001",
   "???",
   "",
   "aka MAJIN EIYU WATARU, 1p",
   USA},

// ROM NUMBER #324
  {0XB77F2E2F,
   "ZERO 4 CHAMP",
   "MEDIA RINGS",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #325
  {0XEE156721,
   "ZERO 4 CHAMP",
   "MEDIA RINGS",
   "MR91003",
   "03/08/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #326
  {0X5C4D1991,
   "BULLFIGHT RING NO HAJA",
   "CREAM",
   "CC-01001",
   "12/08/89",
   "",
   "",
   JAP},

// ROM NUMBER #327
  {0X3E4EAF98,
   "BULLFIGHT RING NO HAJA",
   "CREAM",
   "CC-01001",
   "12/08/89",
   "",
   "",
   JAP},

// ROM NUMBER #328
  {0X8E4D75A8,
   "NEW ZEALAND STORY, THE",
   "TAITO",
   "TP02007",
   "02/23/90",
   "",
   "",
   JAP},

// ROM NUMBER #329
  {0X1772A6BC,
   "NEW ZEALAND STORY, THE",
   "TAITO",
   "TP02007",
   "02/23/90",
   "",
   "",
   JAP},

// ROM NUMBER #330
  {0XB01F70C2,
   "NARAZUMO NO SENTOU BUTAI BLOODY WOLF",
   "DATA EAST",
   "DE89003",
   "09/01/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #331
  {0X47AFE6D7,
   "BLOODY WOLF",
   "DATA EAST",
   "TGX040037",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #332
  {0X99033916,
   "TOILET KIDS",
   "MEDIA RINGS",
   "MR92005",
   "03/06/92",
   "",
   "",
   JAP},

// ROM NUMBER #333
  {0X53B7784B,
   "TOILET KIDS",
   "MEDIA RINGS",
   "",
   "03/06/92",
   "",
   "",
   JAP},

// ROM NUMBER #334
  {0XB64DE6FD,
   "ALIEN CRUSH",
   "NAXAT",
   "",
   "???",
   "",
   "",
   USA | PINBALL_KEY},

// ROM NUMBER #335
  {0X60EDF4E1,
   "ALIEN CRUSH",
   "NAXAT",
   "NX63001",
   "09/14/88",
   "",
   "",
   JAP | PINBALL_KEY},

// ROM NUMBER #336
  {0X2762792B,
   "DEVIL'S CRUSH",
   "NAXAT",
   "",
   "???",
   "",
   "2p",
   USA | TWO_PART_ROM | PINBALL_KEY},

// ROM NUMBER #337
  {0X166A0E44,
   "DEVIL'S CRASH",
   "NAXAT",
   "NX90004",
   "07/20/90",
   "",
   "2p",
   JAP | TWO_PART_ROM | PINBALL_KEY},

// ROM NUMBER #338
  {0XD233C05A,
   "BURNING ANGEL",
   "NAXAT",
   "NX90008",
   "12/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #339
  {0X17A47D0D,
   "BURNING ANGEL",
   "NAXAT",
   "NX90008",
   "12/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #340
  {0X033E8C4A,
   "CHASE HQ",
   "TAITO",
   "TP02006",
   "01/26/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #341
  {0X6F4FD790,
   "CHASE HQ",
   "TAITO",
   "TP02006",
   "01/26/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #342
  {0XD6FC51CE,
   "STRIP FIGHTER II",
   "GAMES EXPRESS",
   "T4955754200984",
   "???",
   "",
   "2p",
   JAP},

// ROM NUMBER #343
  {0X5F2C9A45,
   "STRIP FIGHTER II",
   "GAMES EXPRESS",
   "T4955754200984",
   "???",
   "",
   "2p",
   JAP},

// ROM NUMBER #344
  {0X85AA49D0,
   "SINISTRON",
   "IGS",
   "ITGX10007",
   "???",
   "",
   "aka VIOLENT SOLDIER",
   JAP},

// ROM NUMBER #345
  {0X1BC36B36,
   "VIOLENT SOLDIER",
   "IGS",
   "AI02005",
   "12/14/90",
   "",
   "aka SINISTRON, 1p",
   JAP},

// ROM NUMBER #346
  {0X34FD4EF2,
   "VIOLENT SOLDIER",
   "IGS",
   "AI02005",
   "12/14/90",
   "",
   "aka SINISTRON, 1p",
   JAP},

// ROM NUMBER #347
  {0X70D90E20,
   "WORLD COURT TENNIS",
   "NAMCO",
   "TGX020019",
   "???",
   "",
   "4p",
   USA},

// ROM NUMBER #348
  {0X11A36745,
   "WORLD COURT TENNIS",
   "NAMCO",
   "NC63004",
   "08/11/88",
   "",
   "",
   JAP},

// ROM NUMBER #349
  {0XDCA24A76,
   "FANTASY ZONE",
   "SEGA",
   "H49G-1001",
   "10/14/88",
   "",
   "",
   USA},

// ROM NUMBER #350
  {0X72CB0F9D,
   "FANTASY ZONE",
   "SEGA",
   "H49G-1001",
   "10/14/88",
   "",
   "",

   },

// ROM NUMBER #351
  {0X05453628,
   "ALICE IN WONDERDREAM",
   "FACE",
   "FA02-007",
   "12/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #352
  {0X12C4E6FD,
   "ALICE IN WONDERDREAM",
   "FACE",
   "FA02-007",
   "12/07/90",
   "",
   "",
   JAP},

// ROM NUMBER #353
  {0XA9A94E1B,
   "NEUTOPIA",
   "HUDSON V1",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #354
  {0X30D4BD0E,
   "NEUTOPIA",
   "HUDSON V2",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #355
  {0X9D1A0F5A,
   "NEUTOPIA",
   "HUDSON V1",
   "HC89022",
   "11/17/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #356
  {0X9C49EF11,
   "NEUTOPIA",
   "HUDSON V2",
   "HC89022",
   "11/17/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #357
  {0XAE26F30F,
   "NEUTOPIA II",
   "HUDSON",
   "TGX060078",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #358
  {0XF0AB946E,
   "NEUTOPIA II",
   "HUDSON V1",
   "HC91047",
   "09/27/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #359
  {0X2B94AEDC,
   "NEUTOPIA II",
   "HUDSON V2",
   "HC91047",
   "09/27/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #360
  {0X595BB22A,
   "NECTARIS",
   "HUDSON",
   "HC63016",
   "02/09/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #361
  {0X0243453B,
   "NECTARIS",
   "HUDSON",
   "HC63016",
   "02/09/89",
   "",
   "aka MILITARY MADNESS, 2p",
   JAP},

// ROM NUMBER #362
  {0X93F316F7,
   "MILITARY MADNESS",
   "HUDSON",
   "TGX030015",
   "???",
   "",
   "aka NECTARIS, 2p",
   USA},

// ROM NUMBER #363
  {0X106BB7B2,
   "BATMAN",
   "SUNSOFT",
   "SS90003",
   "10/12/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #364
  {0X92C919EA,
   "BATMAN",
   "SUNSOFT",
   "SS90003",
   "10/12/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #365
  {0X25DE250A,
   "AOI BLINK",
   "HUDSON",
   "HC90030",
   "04/27/90",
   "",
   "aka BLUE BLINK",
   JAP},

// ROM NUMBER #366
  {0X08A09B9A,
   "AOI BLINK",
   "HUDSON",
   "HC90030",
   "04/27/90",
   "",
   "aka BLUE BLINK",
   JAP},

// ROM NUMBER #367
  {0X79362389,
   "1943 KAI",
   "CAPCOM",
   "NX91002",
   "03/22/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #368
  {0XFDE08D6D,
   "1943 KAI",
   "NAXAT",
   "NX91002",
   "03/22/91",
   "",
   "2p",
   JAP},

// ROM NUMBER #369
  {0X4BD38F17,
   "GOMOLA SPEED",
   "UPL",
   "UP02002",
   "09/28/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #370
  {0X6E297E49,
   "GOMOLA SPEED",
   "UPL",
   "UP02002",
   "09/28/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #371
  {0X00C38E69,
   "RASTAN SAGA II",
   "TAITO",
   "TP02012",
   "07/06/90",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #372
  {0X85B85FF9,
   "RASTAN SAGA II",
   "TAITO",
   "TP02012",
   "07/06/90",
   "",
   "",
   JAP},

// ROM NUMBER #373
  {0X70749841,
   "TV SPORTS BASKETBALL",
   "CINEMAWARE",
   "",
   "04/29/93",
   "",
   "5p",
   JAP},

// ROM NUMBER #374
  {0X9A41C638,
   "TV SPORTS BASKETBALL",
   "CINEMAWARE",
   "",
   "???",
   "",
   "5p",
   USA},

// ROM NUMBER #375
  {0XDA059C9B,
   "TV SPORTS FOOTBALL",
   "VICTOR",
   "JC63008",
   "03/29/91",
   "",
   "",
   JAP},

// ROM NUMBER #376
  {0X968D908A,
   "TV SPORTS FOOTBALL",
   "VICTOR",
   "JC63008",
   "03/29/91",
   "",
   "",
   JAP},

// ROM NUMBER #377
  {0XBB3CA04A,
   "BUBBLEGUM CRASH",
   "ARTMIC",
   "NX91005",
   "12/06/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #378
  {0X0D766139,
   "BUBBLEGUM CRASH",
   "ARTMIC",
   "NX91005",
   "12/06/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #379
  {0XFAE0FC60,
   "ORDER OF THE GRIFFON",
   "SSL",
   "TGX040072",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #380
  {0XCAE1F5DB,
   "ORDER OF THE GRIFFON",
   "SSL",
   "TGX040072",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #381
  {0X4CAA6BE9,
   "SILENT DEBUGGERS",
   "DATA EAST",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #382
  {0X616EA179,
   "SILENT DEBUGGERS",
   "DATA EAST",
   "DE90004",
   "03/29/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #383
  {0X9FB4DE48,
   "RACING SPIRITS",
   "IREM",
   "ICO3006",
   "07/19/91",
   "",
   "",
   JAP},

// ROM NUMBER #384
  {0X3E79734C,
   "RACING SPIRITS",
   "IREM",
   "ICO3006",
   "07/19/91",
   "",
   "",
   JAP},

// ROM NUMBER #385
  {0XAE9FE1AA,
   "NINJA SPIRIT",
   "IREM",
   "TGX040050",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #386
  {0X0590A156,
   "NINJA SPIRIT",
   "IREM",
   "IC02004",
   "07/06/90",
   "",
   "",
   JAP},

// ROM NUMBER #387
  {0XDCF3675C,
   "DRAGON SPIRIT",
   "NAMCO",
   "",
   "12/26/88",
   "",
   "",
   USA},

// ROM NUMBER #388
  {0X01A76935,
   "DRAGON SPIRIT",
   "NAMCO",
   "NC63003",
   "12/26/88",
   "",
   "",
   JAP},

// ROM NUMBER #389
  {0X1E1D0319,
   "DARIUS PLUS",
   "TAITO - SGX",
   "NAPH-1009",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #390
  {0XBEBFE042,
   "DARIUS",
   "...",
   "...",
   "...",
   "",
   "",

   },

// ROM NUMBER #391
  {0XBC655CF3,
   "SHINOBI",
   "ASMIK",
   "AS01001",
   "12/08/89",
   "",
   "",
   JAP},

// ROM NUMBER #392
  {0X471903C6,
   "SHINOBI",
   "ASMIK",
   "AS01001",
   "12/08/89",
   "",
   "",
   JAP},

// ROM NUMBER #393
  {0XC8A412E1,
   "VIGILANTE",
   "IREM",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #394
  {0XEB4E600B,
   "VIGILANTE",
   "IREM",
   "IC63001",
   "01/14/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #395
  {0XE4124FE0,
   "VIGILANTE",
   "IREM",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #396
  {0XCACC06FB,
   "ANKOKO DENSETSU",
   "ATLUS",
   "BG01003",
   "06/28/89",
   "",
   "aka LEGENDARY AXE II",
   JAP},

// ROM NUMBER #397
  {0X07A226FB,
   "LEGENDARY AXE, THE",
   "NEC",
   "TGX020003",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #398
  {0X088D896D,
   "LEGENDARY AXE II, THE",
   "NEC",
   "",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #399
  {0XCFCFC7BE,
   "FINAL LAP TWIN",
   "NAMCO",
   "NC89003",
   "07/07/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #400
  {0XC8C084E3,
   "FINAL LAP TWIN",
   "NAMCO",
   "NC89003",
   "07/07/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #401
  {0X854C37B3,
   "FINAL LAP TWIN",
   "NAMCO",
   "NC89003",
   "07/07/89",
   "",
   "2p",
   USA},

// ROM NUMBER #402
  {0XCEC3D28A,
   "R TYPE I",
   "IREM",
   "HC63007",
   "03/25/88",
   "",
   "1p",
   JAP},

// ROM NUMBER #403
  {0X149D0511,
   "R TYPE I",
   "IREM",
   "HC63007",
   "03/25/88",
   "",
   "1p (BOOTLEG TRAINER VERSION)",
   JAP},

// ROM NUMBER #404
  {0XF207ECAE,
   "R TYPE II",
   "IREM",
   "HC63009",
   "06/03/88",
   "",
   "1p",
   JAP},

// ROM NUMBER #405
  {0X98B03EC9,
   "R TYPE COMPLETE",
   "",
   "",
   "???",
   "",
   "CRACKED TO WORK ON JAP PC-E",
   USA},

// ROM NUMBER #406
  {0X9E2CF932,
   "R TYPE COMPLETE",
   "",
   "",
   "???",
   "",
   "",
   USA | US_ENCODED},

// ROM NUMBER #407
  {0XE6458212,
   "PARASOL STARS",
   "TAITO",
   "",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #408
  {0X786D9BBD,
   "PARASOL STARS",
   "TAITO",
   "",
   "???",
   "",
   "2p",
   JAP},

// ROM NUMBER #409
  {0X45885AFB,
   "PARASOL STARS",
   "TAITO",
   "",
   "???",
   "",
   "2p",
   JAP},

// ROM NUMBER #410
  {0X51E86451,
   "PARASOL STARS",
   "TAITO",
   "",
   "???",
   "",
   "2p",
   USA},

// ROM NUMBER #411
  {0X1E2CBCF8,
   "DUNGEON EXPLORER",
   "",
   "",
   "???",
   "",
   "5p",
   USA | TWO_PART_ROM},

// ROM NUMBER #412
  {0XF79657DD,
   "DUNGEON EXPLORER",
   "HUDSON",
   "HC63015",
   "03/04/89",
   "",
   "5p",
   JAP},

// ROM NUMBER #413
  {0X1B1A80A2,
   "DUNGEON EXPLORER",
   "ATLUS",
   "HC63015",
   "03/04/89",
   "",
   "5p",
   JAP},

// ROM NUMBER #414
  {0X231B1535,
   "TATSUJIN",
   "TAITO",
   "...",
   "...",
   "",
   "...",
   JAP},

// ROM NUMBER #415
  {0XA6088275,
   "TATSUJIN",
   "TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #416
  {0X589D33EB,
   "KING OF CASINO",
   "VICTOR",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #417
  {0XE4B3415C,
   "KING OF CASINO",
   "VICTOR",
   "JC63006",
   "03/30/90",
   "",
   "",
   JAP},

// ROM NUMBER #418
  {0XBF52788E,
   "KING OF CASINO",
   "VICTOR",
   "JC63006",
   "03/30/90",
   "",
   "",
   JAP},

// ROM NUMBER #419
  {0X4938B8BB,
   "POPULOUS",
   "HUDSON",
   "HC91041",
   "04/05/91",
   "",
   "",
   JAP | POPULOUS},

// ROM NUMBER #420
  {0X31E2E7B6,
   "POPULOUS",
   "HUDSON",
   "HC91041",
   "04/05/91",
   "",
   "",
   JAP | POPULOUS},

// ROM NUMBER #421
  {0X850829F2,
   "RAIDEN",
   "SEIBU KAIHATSU",
   "HC91049",
   "11/22/91",
   "",
   "1p",

   },

// ROM NUMBER #422
  {0XC7847DF7,
   "RAIDEN",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #423
  {0XB99A85B6,
   "RAIDEN",
   "SEIBU KAIHATSU",
   "HC91049",
   "11/22/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #424
  {0X2841FD1E,
   "WONDERBOY IN MONSTERLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #425
  {0X02DB6FE5,
   "WONDERBOY IN MONSTERLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #426
  {0X38E2917D,
   "WONDERBOY IN MONSTERLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #427
  {0X72A2C22C,
   "BARI BARI DENSETSU",
   "TAITO",
   "TP01003",
   "11/29/89",
   "",
   "",
   JAP},

// ROM NUMBER #428
  {0XC267E25D,
   "BARI BARI DENSETSU",
   "TAITO",
   "TP01003",
   "11/29/89",
   "",
   "",
   JAP},

// ROM NUMBER #429
  {0XED3A71F8,
   "JACKIE CHAN'S ACTION KUNG FU",
   "HUDSON",
   "TGX040079",
   "???",
   "",
   "1p",
   USA},

// ROM NUMBER #430
  {0XC6FA6373,
   "JACKIE CHAN ACTION KUNGFU",
   "HUDSON",
   "HC90032",
   "01/18/91",
   "",
   "1p",
   JAP},

// ROM NUMBER #431
  {0X3920105A,
   "ANDRE PANZA KICK BOXING",
   "NEC",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #432
  {0X8F02FD20,
   "POWER GOLF",
   "HUDSON",
   "HC89018",
   "05/25/89",
   "",
   "",

   },

// ROM NUMBER #433
  {0XEA324F07,
   "POWER GOLF",
   "HUDSON",
   "HC89018",
   "05/25/89",
   "",
   "",

   },

// ROM NUMBER #434
  {0X7ACB60C8,
   "HIT THE ICE",
   "TAITO",
   "TP03019",
   "09/20/91",
   "",
   "4p",
   JAP},

// ROM NUMBER #435
  {0X775BD3E1,
   "HIT THE ICE",
   "TAITO",
   "TPO3019",
   "09/20/91",
   "",
   "",
   JAP},

// ROM NUMBER #436
  {0X805A34B9,
   "TV SPORTS ICE HOCKEY",
   "VICTOR",
   "JC63013",
   "04/29/93",
   "",
   "",
   JAP},

// ROM NUMBER #437
  {0X4DF54B81,
   "TV SPORTS HOCKEY",
   "NEC",
   "TGX030064",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #438
  {0X04BF5EAF,
   "TV SPORTS HOCKEY",
   "NEC",
   "TGX030064",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #439
  {0X4CEF0456,
   "WALLABY!!",
   "MASYNYA",
   "NCS90005",
   "12/14/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #440
  {0X0112D0C7,
   "WALLABY!!",
   "MASYNYA",
   "NCS90005",
   "12/14/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #441
  {0X958BCD09,
   "BLODIA",
   "HUDSON",
   "HC90027",
   "03/23/90",
   "",
   "1p",
   JAP},

// ROM NUMBER #442
  {0X05A4B72E,
   "TIMEBALL",
   "HUDSON",
   "",
   "???",
   "",
   "1p (AKA BLODIA)",
   USA},

// ROM NUMBER #443
  {0X09509315,
   "TWIN COBRA",
   "TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #444
  {0XA586D190,
   "TWIN COBRA",
   "TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #445
  {0X43EFC974,
   "PARANOIA",
   "NAXAT",
   "NX90001",
   "03/01/90",
   "",
   "aka PSYCHOSIS, 2p",
   JAP},

// ROM NUMBER #446
  {0X9893E0E6,
   "PARANOIA",
   "NAXAT",
   "NX90001",
   "03/01/90",
   "",
   "aka PSYCHOSIS, 2p",
   JAP},

// ROM NUMBER #447
  {0X73E994A0,
   "PARANOIA",
   "NAXAT",
   "NX90001",
   "03/01/90",
   "",
   "aka PSYCHOSIS, 2p",
   JAP},

// ROM NUMBER #448
  {0X73614660,
   "21 EMON",
   "NEC",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #449
  {0X5E4FA713,
   "ARTIST TOOL",
   "HUDSON",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #450
  {0X320F5018,
   "TENNOKOE BANK",
   "",
   "HC692",
   "XX-XX-91",
   "",
   "EXTRA BACKUP RAM CARD",
   JAP},

// ROM NUMBER #451
  {0X968770F6,
   "BE BALL",
   "TAISANG VERSION",
   "HC90028",
   "03/30/90",
   "",
   "aka CHEW-MAN-FU, 2p",
   JAP},

// ROM NUMBER #452
  {0X6EAB778C,
   "R TYPE II",
   "TAISANG VERSION",
   "HC63009",
   "06/03/88",
   "",
   "1p",
   JAP},

// ROM NUMBER #453
  {0X4F2BD39F,
   "HYPERDYNE SIDEARMS",
   "TAISANG VERSION",
   "H54G-1004",
   "07/14/89",
   "",
   "",
   JAP},

// ROM NUMBER #454
  {0XDE963B7E,
   "HYPERDYNE SIDEARMS",
   "MAGAE CHIP VERSION",
   "H54G-1004",
   "07/14/89",
   "",
   "",
   JAP},

// ROM NUMBER #455
  {0XB0BA689F,
   "DARIUS ALPHA",
   "NEC AVENUE & TAITO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #456
  {0XE1A73797,
   "BENKEI",
   "SUNSOFT",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #457
  {0X02A578C5,
   "FINAL SOLDIER SPECIAL VERSION",
   "HUDSON",
   "",
   "XX-XX-91",
   "",
   "1p",
   JAP},

// ROM NUMBER #458
  {0X57F183AE,
   "GUNHED SPECIAL VERSION",
   "HUDSON",
   "",
   "XX-XX-89",
   "",
   "",
   JAP | TWO_PART_ROM},

// ROM NUMBER #459
  {0X95F90DEC,
   "GAI FLAME",
   "MASYNYA & NCS",
   "",
   "XX-XX-90",
   "",
   "",
   JAP},

// ROM NUMBER #460
  {0XCC799D92,
   "HATRIS",
   "BULLET PROOF",
   "MC91002",
   "05/24/91",
   "",
   "",
   JAP},

// ROM NUMBER #461
  {0X8E71D4F3,
   "ADVENTURE ISLAND",
   "HUDSON",
   "",
   "???",
   "",
   "aka DRAGON'S CURSE, 1p",
   JAP},

// ROM NUMBER #462
  {0X62EC2956,
   "WORLD COURT TENNIS",
   "NAMCO",
   "NC63004",
   "08/11/88",
   "",
   "",
   JAP},

// ROM NUMBER #463
  {0XC4EB68A5,
   "WORLD COURT TENNIS",
   "NAMCO",
   "NC63004",
   "08/11/88",
   "",
   "",
   JAP},

// ROM NUMBER #464
  {0X0AD97B04,
   "J.LEAGUE GREATEST ELEVEN SOCCER",
   "NIHON BUSSAN",
   "",
   "XX-XX-93",
   "",
   "",
   JAP},

// ROM NUMBER #465
  {0X61B80005,
   "KNIGHT RIDER SPECIAL",
   "PACK-IN-VIDEO",
   "PV1003",
   "12/22/89",
   "",
   "1p",
   JAP},

// ROM NUMBER #466
  {0XF8861456,
   "MAHJONG GOKU SPECIAL",
   "SUNSOFT",
   "SS90002",
   "08/10/90",
   "",
   "",
   JAP},

// ROM NUMBER #467
  {0XB101B333,
   "MAKAIPRN? CRAZY PLATFORMER",
   "",
   "NAXAT",
   "XX-XX-90",
   "",
   "",
   JAP},

// ROM NUMBER #468
  {0X625221A6,
   "MOMO TAROU DENSETSU TURBO",
   "HUDSON",
   "HC90034",
   "07/20/90",
   "",
   "",
   JAP},

// ROM NUMBER #469
  {0XD9E1549A,
   "MOMO TAROU DENTETSU II",
   "HUDSON",
   "HC90040",
   "12/22/90",
   "",
   "",
   JAP},

// ROM NUMBER #470
  {0X0441D85A,
   "NAZONO?????",
   "",
   "",
   "???",
   "",
   " JAP",

   },

// ROM NUMBER #471
  {0X20A7D128,
   "NAXAT STADIUM",
   "NAXAT",
   "NX90006",
   "10/26/90",
   "",
   "",
   JAP},

// ROM NUMBER #472
  {0X52520BC6,
   "CD-ROM SYSTEM VER. 2.00",
   "NEC",
   "",
   "???",
   "",
   "51356:128",
   JAP | CD_SYSTEM},

// ROM NUMBER #473
  {0X9759A20D,
   "SUPER CD-ROM2 SYSTEM VER. 3.00",
   "NEC",
   "",
   "???",
   "",
   "",
   USA | CD_SYSTEM},

// ROM NUMBER #474
  {0XC5FDFA89,
   "POWER LEAGUE II",
   "HUDSON",
   "HC89020",
   "08/08/89",
   "",
   "2p",
   JAP},

// ROM NUMBER #475
  {0X8AA4B220,
   "POWER LEAGUE III",
   "HUDSON",
   "HC90037",
   "08/10/90",
   "",
   "2p",
   JAP},

// ROM NUMBER #476
  {0X7D3E6F33,
   "POWER LEAGUE `93",
   "HUDSON",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #477
  {0XFAA6E187,
   "PUZZLE BOY",
   "TELENET",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #478
  {0XF2E6856D,
   "QUIZTOKO ??",
   "GAMES EXPRESS",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #479
  {0X2BC023FC,
   "SUPER MOMO TAROU DENTETSU II",
   "SUMMER PROJECT",
   "HC91050",
   "12/20/91",
   "",
   "",
   JAP},

// ROM NUMBER #480
  {0X61A6E210,
   "TSUPPARI SUMO WRESTLING GAME",
   "NAXAT",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #481
  {0X10B60601,
   "TV SPORTS BASKETBALL",
   "CINEMAWARE",
   "",
   "04/29/93",
   "",
   "5p",
   JAP},

// ROM NUMBER #482
  {0XE7529890,
   "TV SPORTS ICE HOCKEY",
   "VICTOR",
   "JC63013",
   "04/29/93",
   "",
   "",
   JAP},

// ROM NUMBER #483
  {0X14DAF737,
   "TV SPORTS FOOTBALL",
   "VICTOR",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #484
  {0XF45AFBCA,
   "CADASH",
   "TAITO",
   "",
   "???",
   "",
   "",
   USA | US_ENCODED},

// ROM NUMBER #485
  {0X0258ACCB,
   "LEGEND OF HERO TONMA, THE",
   "IREM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #486
  {0X6257CCE7,
   "SPACE HARRIER",
   "NEC AVENUE",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #487
  {0X756A1802,
   "NEW ADVENTURE ISLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #488
  {0X85CC9B60,
   "DEAD MOON",
   "NATSUME",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #489
  {0XC2287894,
   "DEEP BLUE",
   "PACK-IN-VIDEO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #490
  {0X390710EC,
   "CYBER CORE",
   "IGS",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #491
  {0XE84890A5,
   "CHASE HQ",
   "TAITO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #492
  {0X2BBF3090,
   "BRAVOMAN",
   "",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #493
  {0X8BF34FFA,
   "BOMBERMAN",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #494
  {0X26020C77,
   "BOMBERMAN `93",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #495
  {0XC02B1B59,
   "AERO BLASTERS",
   "KANEKO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #496
  {0X2A3E08E2,
   "DROP OFF",
   "DATA EAST",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #497
  {0X2739B927,
   "PAC LAND",
   "NAMCO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #498
  {0X72814ACB,
   "ORDYNE",
   "NAMCO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #499
  {0XC159761B,
   "NIGHT CREATURES",
   "MANLEY & ASSOCIATES",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #500
  {0XC81D0371,
   "PSYCHOSIS",
   "NAXAT",
   "",
   "???",
   "",
   "aka PARANOIA",
   USA},

// ROM NUMBER #501
  {0X5157A395,
   "VICTORY RUN",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #502
  {0X500472D4,
   "TIGER ROAD",
   "CAPCOM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #503
  {0X9C7A8EE4,
   "TRICKY KICK",
   "IGS",
   "",
   "???",
   "",
   "aka TRICKY",
   USA},

// ROM NUMBER #504
  {0X0C7627A9,
   "WORLD SPORTS COMPETITION",
   "",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #505
  {0X4161F202,
   "WORLD WPORTS COMPETITION",
   "",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #506
  {0XF0CC3363,
   "SUPER VOLLEY BALL",
   "VIDEO SYSTEM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #507
  {0X72D6860B,
   "TIME CRUISE",
   "FACE",
   "",
   "???",
   "",
   "",
   USA | PINBALL_KEY},

// ROM NUMBER #508
  {0XA019B724,
   "SPLATTERHOUSE",
   "NAMCO",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #509
  {0X284EBE25,
   "SOLDIER BLADE",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #510
  {0X05054F4F,
   "SIDEARMS",
   "CAPCOM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #511
  {0XEB9452F0,
   "MOTO ROADER",
   "MASYNYA",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #512
  {0X93F05168,
   "POWER GOLF",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #513
  {0X574352C6,
   "CD ROM 2 SYSTEM 3.0",
   "NEC / HUDSON",
   "",
   "???",
   "",
   "51401:128",
   USA | CD_SYSTEM},

// ROM NUMBER #514
  {0X6A628982,
   "ALTERED BEAST",
   "SEGA",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #515
  {0X4D344C8C,
   "WONDERBOY IN MONSTERLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #516
  {0X9BB8D362,
   "JAMANOID",
   "THE HU62680 TEAM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #517
  {0X67AEDE77,
   "WONDERBOY IN MONSTERLAND",
   "HUDSON",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #518
  {0X6976D5B3,
   "15 IN 1 MEGA-COLLECTION",
   "IMAGE",
   "",
   "'92",
   "",
   "",
   USA},

// ROM NUMBER #519
  {0X6203DE23,
   "QUIZTOKO ??",
   "GAMES EXPRESS",
   "",
   "???",
   "",
   "",
   JAP},
// ROM NUMBER #520
  {0XF84AE70B,
   "HYPERDYNE SIDEARMS",
   "NEC AVENUE / CAPCOM",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #521
  {0XFA7E5D66,
   "SILENT DEBUGGERS",
   "DATA EAST",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #522
  {0XBF7F6E42,
   "JAMANOID",
   "THE HU62680 TEAM",
   "",
   "???",
   "",
   "old version",

   },

// ROM NUMBER #523
  {0X78F1DE1C,
   "R TYPE I",
   "HUDSON / IREM",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #524
  {0X24C82EBE,
   "TALESPIN",
   "NEC",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #525
  {0X2E278CCB,
   "TENSEIRYU SAINT DRAGON",
   "AICOM",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #526
  {0X3D30D358,
   "TRICKY KICK",
   "IGS",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #527
  {0X931B601F,
   "YO'BRO",
   "ICOM",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #528
  {0X706190F0,
   "ORDER OF GRIFFON",
   "WESTWOOD ASSOCIATES",
   "",
   "???",
   "",
   "",
   USA},

// ROM NUMBER #529
  {0X22E67896,
   "OUT RUN",
   "SEGA",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #530
  {0XBEED81F,
   "DETANA!! TWINBEE",
   "KONAMI",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #531
  {0XC89CE75A,
   "DRAGON SABER",
   "NAMCO",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #532
  {0XE7738B25,
   "DRAGON SPIRIT",
   "NAMCO",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #533
  {0XE4A7D4DC,
   "DROP ROCK",
   "DATA EAST",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #534
  {0XAC2D7094,
   "DUNGEON EXPLORER",
   "HUDSON / ALTUS",
   "",
   "???",
   "",
   "",

   },

// ROM NUMBER #535
  {0XF652FA19,
   "OPERATION WOLF",
   "NEC AVENUE",
   "",
   "???",
   "",
   "2p",
   JAP},

// ROM NUMBER #536
  {0XBD914B8,
   "PARODIUS",
   "KONAMI",
   "",
   "???",
   "",
   "",
   JAP},

// ROM NUMBER #537
  {0X90E6BF49,
   "UNREADABLE TITLE",
   "HUDSON",
   "",
   "'88",
   "",
   "",
   JAP},

// ROM NUMBER #538
  {0X7E3C367B,
   "KICKBALL",
   "NCS",
   "",
   "'90",
   "",
   "",
   USA},

//ROM NUMBER #539
  {0X699B148F,
   "NON WORKING GAME",
   "",
   "",
   "",
   "",
   ""},

// ROM NUMBER #540
  {0XE13A6CE8,
   "BARI BARI DENSETSU",
   "TAITO",
   "TP01003",
   "29-11-89",
   "5M",
   "",
   JAP}



};

/*ROM_TYPE ROM_LIST[NB_ROM] = {
    {//ROM NUMBER 0
    0X8C4588E2    ,"1941 COUNTER ATTACK - HUDSON"
    ,"HC91048"
    ,"23-08-91"
    ,"8M"
    ,"2p"
    ,SUPER_GRAPHX
      | JAP
   },
    {//ROM NUMBER 1
    0X4C2126B0    ,"ALDYNES - HUDSON"
    ,"HC91044"
    ,"22-02-91"
    ,"8M"
    ,"1p"
    ,SUPER_GRAPHX
      | JAP
   },
    {//ROM NUMBER 2
    0XB486A8ED    ,"DAIMAKAIMURA - CAPCOM"
    ,"NAPH-1008"
    ,"27-07-90"
    ,"8M"
    ,"1p"
    ,SUPER_GRAPHX
      | JAP
   },
    {//ROM NUMBER 3
    0X3B13AF61    ,"BATTLE ACE - HUDSON"
    ,"HC89026"
    ,"30-11-89"
    ,"4M"
    ,""
    ,SUPER_GRAPHX
      | JAP
   },
    {//ROM NUMBER 4
    0X1F041166    ,"GRANDZORT"
    ,""
    ,""
    ,""
    ,""
    ,SUPER_GRAPHX
      | JAP
   },
    {//ROM NUMBER 5
    0X0517DA65    ,"GRADIUS - KONAMI"
    ,"KM91001"
    ,"15-11-91"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 6
    0X14FAD3BA    ,"PAC-LAND - NAMCO"
    ,""
    ,""
    ,"2M"
    ,"2p"
   },
    {//ROM NUMBER 7
    0X1B5B1CB1    ,"DIE HARD - NICHIBUTSU"
    ,"NB90003"
    ,"28-09-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 8
    0X25BE2B81    ,"AERO BLASTERS - KANEKO"
    ,"TGX040051"
    ,""
    ,"4M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 9
    0X1B2D0077    ,"TERRA CRESTA II - NIHON BUSSAN"
    ,"NB96002"
    ,"27-11-92"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 10
    0XC356216B    ,"TAKIN IT TO THE HOOP - AICOM"
    ,""
    ,""
    ,""
    ,"2p"
    , USA
   },
    {//ROM NUMBER 11
    0X09A0BFCC    ,"S.C.I. - SPECIAL CRIMINAL INVESTIGATION - TAITO"
    ,"TP03016"
    ,"25-01-91"
    ,"4M"
    ,"4p"
    , USA
   },
    {//ROM NUMBER 12
    0X2CB92290    ,"MR.HELI NO DAI BOUKEN - IREM"
    ,"IC01002"
    ,"01-12-89"
    ,"4M"
    ,"aka MR.HELI's BIG ADVENTURE, 1p"
    , JAP
   },
    {//ROM NUMBER 13
    0X053A0F83    ,"DEEP BLUE - PACK-IN-VIDEO"
    ,""
    ,""
    ,"2M"
    ,"aka DEEP BLUE KAITEI SHINWA, 1p"
   },
    {//ROM NUMBER 14
    0XD15CB6BB    ,"STREET FIGHTER II' CHAMPION EDITION - CAPCOM"
    ,"HE93002"
    ,"12-06-93"
    ,"20M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 15
    0X7632DB90    ,"P 47 THE FREEDOM FIGHTER - AICOM"
    ,"AC89001"
    ,"20-03-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 16
    0X8DEF5AA1    ,"POWER TENNIS - HUDSON"
    ,"HC93062"
    ,"25-06-93"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 17
    0XEECFA5FD    ,"DAVIS CUP TENNIS - LORICIEL"
    ,"TGX040061"
    ,""
    ,"4M"
    ,"4p"
    , USA
   },
    {//ROM NUMBER 18
    0X560D2305    ,"FINAL MATCH TENNIS - HUMAN"
    ,"HM91004"
    ,"01-03-91"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 19
    0X6B319457    ,"SPLATTERHOUSE - NAMCO"
    ,""
    ,""
    ,"4M"
    ,"1p"
   },
    {//ROM NUMBER 20
    0X3219849C    ,"DRAGON SABER - NAMCO"
    ,"NC91005"
    ,"27-12-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 21
    0X3F982D0F    ,"TURRICAN - ACCOLADE"
    ,"ATGX04TUTG"
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 22
    0X25E0F6E9    ,"POWER DRIFT - ASMIK"
    ,"AS02002"
    ,"13-04-90"
    ,"4M"
    ,"TGX020005"
    , JAP
   },
    {//ROM NUMBER 23
    0XE203F223    ,"OUT RUN - SEGA"
    ,"NAPH-1016"
    ,"21-12-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 24
    0XDDC3E809    ,"THUNDER BLADE - SEGA"
    ,"NAPH-1015"
    ,"07-12-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 25
    0X64580427    ,"SPACE HARRIER - NEC AVENUE"
    ,"H67G-1002"
    ,"09-12-88"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 26
    0X2DB4C1FD    ,"GHOST MANOR - ICOM"
    ,"TGX040076"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 27
    0X1C6FF459    ,"SPIN PAIR - MEDIA RINGS"
    ,"MR90002"
    ,"14-12-90"
    ,"2M"
    ,"1p, linkable"
    , JAP
   },
    {//ROM NUMBER 28
    0XD8373DE6    ,"RABIO LEPIUS SPECIAL - VIDEO SYSTEM"
    ,"VS-90003"
    ,"19-10-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 29
    0X03E28CFF    ,"VICTORY RUN - HUDSON"
    ,"HC62003"
    ,"28-12-87"
    ,"2M"
    ,"1p"
   },
    {//ROM NUMBER 30
    0X2CEE30EE    ,"CHAMPIONS FOREVER BOXING - NEC"
    ,"TGX040077"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 31
    0X4A3DF3CA    ,"BARUNBA - NAMCO"
    ,"NC90003"
    ,"27-04-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 32
    0X6923D736    ,"SHANGHAI - HUDSON"
    ,"HC62004"
    ,"30-10-87"
    ,"1M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 33
    0X6C30F0AC    ,"15 IN 1 MEGA COLLECTION - IMAGE"
    ,""
    ,""
    ,""
    ,"BOOTLEG"
    , JAP
   },
    {//ROM NUMBER 34
    0X637BA71D    ,"5 IN 1 FAMI COLLECTION - IMAGE"
    ,""
    ,""
    ,""
    ,"BOOTLEG"
    , JAP
   },
    {//ROM NUMBER 35
    0X67AAB7A1    ,"ZIPANG - PACK-IN-VIDEO"
    ,"PV-1005"
    ,"14-12-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 36
    0X4A135429    ,"DARKWING DUCK - DISNEY"
    ,"TGX040066"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 37
    0X56739BC7    ,"DEAD MOON - NATSUME"
    ,""
    ,""
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 38
    0X44E7DF53    ,"HATRIS - BULLET PROOF"
    ,"MC91002"
    ,"24-05-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 39
    0XFF898F87    ,"OPERATION WOLF - NEC AVENUE"
    ,"NAPH-1010"
    ,"31-08-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 40
    0XFAECCE20    ,"SALAMANDER - KONAMI"
    ,"KM91002"
    ,"06-12-91"
    ,"2M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 41
    0XF8F85EEC    ,"XEVIOUS - NAMCO"
    ,"NC90004"
    ,"29-06-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 42
    0X0BE0E0A8    ,"DRAGON'S CURSE - HUDSON"
    ,"TGX020039"
    ,""
    ,"2M"
    ,"aka ADVENTURE ISLAND, 1p"
    , USA
   },
    {//ROM NUMBER 43
    0XA5290DD0    ,"SPIRAL WAVE - MEDIA RINGS"
    ,"MR91004"
    ,"13-12-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 44
    0X3AEA2F8F    ,"TRICKY - IGS"
    ,"AI-03004"
    ,"06-07-91"
    ,""
    ,"aka TRICKY KICK"
    , JAP
   },
    {//ROM NUMBER 45
    0X4D539C9F    ,"SKWEEK - VICTOR"
    ,"JC63011"
    ,"02-08-91"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 46
    0XE5E7B8B7    ,"HYPERDYNE SIDEARMS - CAPCOM"
    ,"H54G-1004"
    ,"14-07-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 47
    0XC9D7426A    ,"BREAK IN - NAXAT"
    ,"NX89002"
    ,"10-08-89"
    ,"2M"
    ,"4p"
    , JAP
   },
    {//ROM NUMBER 48
    0X67EC5EC4    ,"DROP ROCK HORA HORA - DATA EAST"
    ,"DE90005"
    ,"30-03-90"
    ,"2M"
    ,"aka DROP OFF"
    , JAP
   },
    {//ROM NUMBER 49
    0X99496DB3    ,"SPACE INVADERS FUKKATSU NO HI - TAITO"
    ,"TP02008"
    ,"02-03-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 50
    0X99F7A572    ,"COLUMNS - LASER SOFT"
    ,"TJ03002"
    ,"29-03-91"
    ,"1M"
    ,"1p, linkable"
    , JAP
   },
    {//ROM NUMBER 51
    0X67573BAC    ,"NINJA GAIDEN - HUDSON"
    ,"HC92052"
    ,"24-01-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 52
    0X4F2844B0    ,"DELIVERY BOY - TONKIN HOUSE"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 53
    0X20EF87FD    ,"FORMATION ARMED F - BIG DON"
    ,"PV-2004"
    ,"23-03-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 54
    0X8C565CB6    ,"ORDYNE - NAMCO"
    ,"NC89004"
    ,"08-09-89"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 55
    0XB24E6504    ,"YO' BRO - ICOM"
    ,"TGX040054"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 56
    0XB2EF558D    ,"LIQUID KIDS - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 57
    0X740491C2    ,"PC DENJIN - HUDSON"
    ,"HC92053"
    ,"20-11-92"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 58
    0XE3284BA7    ,"AIR ZONK - HUDSON"
    ,"TGX040084"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 59
    0XAF2DD2AF    ,"FINAL SOLDIER - HUDSON"
    ,"HC91045"
    ,"05-07-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 60
    0XD50FF730    ,"F1 DREAM - NEC AVENUE"
    ,"H54G-1005"
    ,"25-08-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 61
    0XE14DEE08    ,"F1 CIRCUS - NICHIBUTSU"
    ,"NB89002"
    ,"14-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 62
    0XD7CFD70F    ,"F1 CIRCUS '91 - NICHIBUTSU"
    ,"NB91004"
    ,"12-07-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 63
    0XB268F2A2    ,"F1 CIRCUS '92 - NICHIBUTSU"
    ,""
    ,"1992"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 64
    0XB4D29E3B    ,"CORYOON CHILD OF DRAGON - NAXAT"
    ,"NX91004"
    ,"29-11-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 65
    0X442405D5    ,"DRAGON EGG! - MASYNYA"
    ,"NCS91003"
    ,"27-09-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 66
    0XBF3E2CC7    ,"HANI IN THE SKY - FACE"
    ,"FA64-0001"
    ,"01-03-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 67
    0XE88987BB    ,"FIRE PRO WRESTLING: 2ND BOUT - HUMAN"
    ,"HM91005"
    ,"30-08-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 68
    0X534E8808    ,"FIRE PRO WRESTLING 3: LEGEND BOUT - HUMAN"
    ,"HM92006"
    ,"13-11-92"
    ,"8M"
    ,""
    , JAP
   },
    {//ROM NUMBER 69
    0X03883EE8    ,"PSYCHO CHASER - NAXAT"
    ,"NX90003"
    ,"06-04-90"
    ,"2M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 70
    0X2DF97BD0    ,"CYBER COMBAT POLICE - FACE"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 71
    0XA594FAC0    ,"CYBER KNIGHT - TONKIN HOUSE"
    ,"TON90003"
    ,"12-10-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 72
    0X56488B36    ,"SUPER METAL CRUSHER - PACK-IN-VIDEO"
    ,"PV-1007"
    ,"29-11-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 73
    0X25A02BEE    ,"METAL STOKER - FACE"
    ,"FA03-009"
    ,"12-07-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 74
    0X92521F34    ,"IMPOSSAMOLE - NEC"
    ,"TGX040062"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 75
    0X647718F9    ,"PARODIUS - KONAMI"
    ,"KM92003"
    ,"21-02-92"
    ,"8M"
    ,""
    , JAP
   },
    {//ROM NUMBER 76
    0XAD450DFC    ,"HERO AGENT - NEC HOME ELECTRONICS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 77
    0XC28B0D8A    ,"LEGEND OF HERO TONMA, THE - IREM"
    ,"IC03005"
    ,"13-03-91"
    ,"4M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 78
    0XDF10C895    ,"KAISERS QUEST - UPL"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 79
    0XC6F764EC    ,"LADY SWORD - GAMES EXPRESS"
    ,"T4955754200922"
    ,""
    ,"8M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 80
    0X17BA3032    ,"DIGITAL CHAMP - NAXAT"
    ,"NX89003"
    ,"13-10-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 81
    0XF370B58E    ,"GUNBOAT - NEC"
    ,"TGX040060"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 82
    0X97C5EE9A    ,"TOY SHOP BOYS - VICTOR"
    ,"JC63009"
    ,"14-12-90"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 83
    0XA15A1F37    ,"MARCHEN MAZE - NAMCO"
    ,"NC90008"
    ,"11-12-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 84
    0XA80C565F    ,"IMAGE FIGHT - IREM"
    ,"IC02003"
    ,"27-07-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 85
    0XC614116C    ,"KNIGHT RIDER SPECIAL - PACK-IN-VIDEO"
    ,"PV1003"
    ,"22-12-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 86
    0X9107BCC8    ,"TIGER SHARK - NEC AVENUE"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 87
    0X29EEC024    ,"POWER SPORTS - HUDSON"
    ,"HC92058"
    ,"10-10-92"
    ,"4M"
    ,"aka WORLD SPORTS COMPETITION, 5p"
    , JAP
   },
    {//ROM NUMBER 88
    0XF2E46D25    ,"MONSTER PRO WRESTLING - ASK KODANSHA"
    ,"AK91002"
    ,"22-11-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 89
    0X965C95B3    ,"PUZZNIC - TAITO"
    ,"TP02011"
    ,"29-06-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 90
    0XA9AB2954    ,"WORLD JOCKEY - NAMCO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 91
    0XDA9A2DC9    ,"BATTLE ROYAL"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 92
    0X7424452E    ,"FALCON - SPECTRUM HOLOBYTE"
    ,"TGX040067"
    ,""
    ,"4M"
    ,"1p, linkable"
    , USA
   },
    {//ROM NUMBER 93
    0X5CF59D80    ,"DETANA!! TWINBEE - KONAMI"
    ,"KM92004"
    ,"28-02-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 94
    0XD20F382F    ,"TITAN - TITUS"
    ,"NX91001"
    ,"15-03-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 95
    0XDD0EBF8C    ,"MAGICAL CHASE - PALSOFT"
    ,"PL91001"
    ,"15-11-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 96
    0XD7921DF2    ,"SON SON II - NEC AVENUE"
    ,"H54G-1003"
    ,"27-01-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 97
    0XDD175EFD    ,"ATOMIC ROBOKID SPECIAL - UPL"
    ,"UP01001"
    ,"19-01-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 98
    0XE415EA19    ,"NEW ADVENTURE ISLAND - HUDSON"
    ,"TGX040080"
    ,""
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 99
    0X1828D2E5    ,"FIGHTING RUN - NICHIBUTSU"
    ,"NB91005"
    ,"29-11-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 100
    0X59D07314    ,"WONDER MOMO - NAMCO"
    ,"NC64001"
    ,"21-04-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 101
    0X0DF57C90    ,"BIO BOXER - NAMCO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 102
    0X8420B12B    ,"SOLDIER BLADE - HUDSON"
    ,"HC92056"
    ,"10-07-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 103
    0XA9FAB7D2    ,"NIGHT CREATURES - MANLEY & ASSOCIATES"
    ,"TGX040069"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 104
    0XEDA32D95    ,"TALESPIN - NEC"
    ,"TGX040056"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 105
    0X727F4656    ,"STRATEGO - ACCOLADE"
    ,"JC63012"
    ,"24-07-92"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 106
    0XCA72A828    ,"AFTER BURNER II - SEGA"
    ,"NAPH-1011"
    ,"28-09-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 107
    0XCFEC1D6A    ,"TIME CRUISE - FACE"
    ,"TGX040090"
    ,""
    ,"4M"
    ,""
	 ,PINBALL_KEY
      | USA
   },
    {//ROM NUMBER 108
    0X013A747F    ,"DORAEMON NOBITA NO DORABIAN NIGHT - HUDSON"
    ,"HC91051"
    ,"06-12-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 109
    0XC0CB5ADD    ,"POCKY AND ROCKY"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 110
    0X85101C20    ,"DOWNLOAD - NEC AVENUE"
    ,"NAPH-1007"
    ,"22-06-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 111
    0XFFD92458    ,"BODY CONQUEST 2 - GAMES EXPRESS"
    ,"T4955754200953"
    ,""
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 112
    0XB74EC562    ,"OVERRIDE - DEKA"
    ,"DE90006"
    ,"08-01-91"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 113
    0XA3303978    ,"VALKYRIE NO DENSETSU - NAMCO"
    ,"NC90006"
    ,"09-09-90"
    ,"6M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 114
    0XCA12AFBA    ,"TENSEIRYU SAINT DRAGON - AICOM"
    ,"AC90001"
    ,"21-12-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 115
    0XEEB6DD43    ,"DRAGON FIGHTER - TONKIN HOUSE"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 116
    0XC0AF0947    ,"VAMPIRE EMPEROR - MASYNYA"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 117
    0XB926C682    ,"GENPEI TORAMADEN - NAMCO"
    ,"NC90001"
    ,"16-03-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 118
    0X59E44F45    ,"BATTLE LODE RUNNER - HUDSON"
    ,"HS93054"
    ,"10-02-93"
    ,"2M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 119
    0XE6EE1468    ,"LODE RUNNER USHINA WARETA MAIKYUU - PACK-IN-VIDEO"
    ,"PV1004"
    ,"27-07-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 120
    0X2B54CBA2    ,"APPARE! GATEBALL - AZUMA"
    ,"HC63016"
    ,"22-12-88"
    ,"2M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 121
    0XB3EEEA2E    ,"WORLD CIRCUIT - NAMCO"
    ,"NC91004"
    ,"18-10-91"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 122
    0X8F4D9F94    ,"BOUKEN DANSHAKAN DON SUNHEART HEN - IMAX"
    ,"IM92001"
    ,""
    ,""
    ,"aka THE LOST SUNHEART"
    , JAP
   },
    {//ROM NUMBER 123
    0X8E25DC77    ,"KIKI KAIKAI - TAITO"
    ,"TP02009"
    ,"27-03-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 124
    0X9B5EBC58    ,"WINNING SHOT - DATA EAST"
    ,"DE64001"
    ,"03-03-89"
    ,"2M"
    ,"4p"
    , JAP
   },
    {//ROM NUMBER 125
    0XBE8B6E3B    ,"POWER GATE - PACK-IN-VIDEO"
    ,"PV-1008"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 126
    0X3C33E016    ,"CART"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 127
    0X57A436A2    ,"JACK NICKLAUS TURBO GOLF - ACCOLADE"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 128
    0X5C78FEE1    ,"MAISON IKKOKU - FUJITV"
    ,"MC66680"
    ,"04-08-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 129
    0X61A2935F    ,"RAISHISU"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 130
    0X6C34AAEA    ,"MAHJONG SHIKAKA RETSUDEN MAHJONG WARS - NICHIBUTSU"
    ,"NB1001"
    ,"01-02-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 131
    0X6FD6827C    ,"GAIA NO MONSHO - NCS"
    ,"NCS63001"
    ,"23-09-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 132
    0X91E6896F    ,"RYUKYU - FACE"
    ,""
    ,"26-10-90"
    ,"2M"
    ,"FA02-005, 1p"
    , JAP
   },
    {//ROM NUMBER 133
    0XA2A0776E    ,"WAI WAI MAHJONG - VIDEO SYSTEM"
    ,"VS-89001"
    ,"19-06-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 134
    0XB5326B16    ,"SUPER DODGE BALL - TONKIN HOUSE"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 135
    0XBA4D0DD4    ,"HANA TAHKA DAKA - TAITO"
    ,"TP03018"
    ,"09-08-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 136
    0XC150637A    ,"JIMMU DENSHO YAKSA - WOLF TEAM"
    ,"BG01003"
    ,"28-06-89"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 137
    0XC8C7D63E    ,"JYUOHKI - SEGA"
    ,"HG8G-1006"
    ,"29-09-89"
    ,"4M"
    ,"aka ALTERED BEAST, 1p"
    , JAP
   },
    {//ROM NUMBER 138
    0XCC7D3EEB    ,"BONZE ADVENTURE - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 139
    0XD4C5AF46    ,"MAKYO DENSETSU - ATLUS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 140
    0XF131B706    ,"CRAZY JAPPY PLATFORMER"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 141
    0X469A0FDF    ,"SHIRYOU SENSEN - FUN PROJECT"
    ,"JC63002"
    ,"24-03-89"
    ,"2M"
    ,"aka WAR OF THE DEAD, 1p"
    , JAP
   },
    {//ROM NUMBER 142
    0X65FDB863    ,"NEKKETSU KOUKOU DODGEBALL BU PC BANGAI HEN - TECHNOS"
    ,"NX90002"
    ,"30-03-90"
    ,"2M"
    ,"aka HOT BLOOD HIGHSCHOOL DODGEBALL"
    , JAP
   },
    {//ROM NUMBER 143
    0X53109AE6    ,"JASEIKIN NECROMANCER - HUDSON"
    ,"HC62005"
    ,"22-01-88"
    ,"1M"
    ,""
    , JAP
   },
    {//ROM NUMBER 144
    0X80C3F824    ,"YOUKAI DOCHUKI - NAMCO"
    ,"NC62001"
    ,""
    ,""
    ,"aka GHOST TRAVEL STORY"
    , JAP
   },
    {//ROM NUMBER 145
    0X34E089A9    ,"PRO YAKYUU WORLD STADIUM - NAMCO"
    ,"NC63001"
    ,"20-05-88"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 146
    0XF70112E5    ,"TORIYUU SIYOUJIN NO JITSEN KABUSHIKI BAI BAI GAME - INTEC"
    ,"IG89001"
    ,"01-11-89"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 147
    0X5CDB3F5B    ,"OUTLIVE - SUNSOFT"
    ,"SS89001"
    ,"17-03-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 148
    0XB122787B    ,"SENGOKU MAHJONG - HUDSON"
    ,"HC63010"
    ,"08-07-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 149
    0XF022BE13    ,"TAKEDA SHINGEN - AICOM"
    ,"AC89002"
    ,"28-07-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 150
    0XC0905CA9    ,"YUU YUU JINSEI - TAKARA"
    ,"HC63008"
    ,"22-04-88"
    ,"2M"
    ,"aka VICTORY LIFE, 5p"
    , JAP
   },
    {//ROM NUMBER 151
    0XBE62EEF5    ,"MAKAI HAKKENDEN SHADA - DATA EAST"
    ,"DE89002"
    ,"01-04-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 152
    0XF999356F    ,"SADAKICHI SABAN HIDEYOSHI NO OUGON - HUDSON"
    ,"HC63014"
    ,"18-11-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 153
    0X1CAD4B7F    ,"USA PRO BASKETBALL - AICOM"
    ,"AC89003"
    ,"01-12-89"
    ,"2M"
    ,""
    , USA
   },
    {//ROM NUMBER 154
    0XA9084D6E    ,"KAIZOU NINGEN SHUBIBIMAN - MASYNYA"
    ,"NCS89004"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 155
    0X27A4D11A    ,"GANBARE! GOLF BOYS - MASYNYA"
    ,"NCS89003"
    ,"28-03-89"
    ,"2M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 156
    0XEA751E82    ,"JOHN GOLF - ACCOLADE"
    ,""
    ,"'89"
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 157
    0X8672717C    ,"UNKNOWN GAME"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 158
    0X23EC8970    ,"SHOGI SHODAN ICCHOKUSEN - HOMEDATA"
    ,"HD90001"
    ,"10-08-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 159
    0XE86249A4    ,"UNKNOWN GAME"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 160
    0XC3212C24    ,"CIRCUS LIDO - UNI POST"
    ,"PJ91001"
    ,"06-04-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 161
    0X457F2BC4    ,"SHOGI SHOSHINSA MUYO - HOMEDATA"
    ,"HD91013"
    ,"29-11-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 162
    0XCAB21B2E    ,"CHIKUDENYA TOUBEE - BIT2"
    ,"NX89004"
    ,"26-01-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 163
    0XC7327632    ,"HISOU KIHEI SERD GAI SHADOW - MASYNYA"
    ,"NCS90002"
    ,"23-02-90"
    ,""
    ,""
	 ,TWO_PART_ROM
      | JAP
   },
    {//ROM NUMBER 164
    0XF4148600    ,"MAHJONG GAKUEN MILD - FACE"
    ,"FA02-004"
    ,"29-06-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 165
    0XC42B6D76    ,"BENKEI GAIDEN - SUNSOFT"
    ,"SS89002"
    ,"22-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 166
    0X00F83029    ,"NO TITLE - MASYNYA"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 167
    0XDC47434B    ,"SINDIBAD CHITEI NO DAI MAKYU - IGS"
    ,"AI-02002"
    ,"02-06-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 168
    0XCF73D8FC    ,"SUSANO OH DENSETSU - HUDSON"
    ,"HC89017"
    ,"27-04-89"
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 169
    0X99F2865C    ,"MANIAC PRO WRESTLING - HUDSON"
    ,"HC89025"
    ,"25-05-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 170
    0XFB0FDCFE    ,"NECROS NO YOUSAI - ASK KODANSHA"
    ,"AK90001"
    ,"20-04-90"
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 171
    0XA71D70D0    ,"GAI FLAME - MASYNYA"
    ,"NCS90001"
    ,"26-01-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 172
    0XF5B90D55    ,"MAHJONG GAKUEN TOUMA SHIRO TOJO - FACE"
    ,"FA01-003"
    ,"24-11-89"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 173
    0XCFC5A395    ,"JIGOKU MEGURI - TAITO"
    ,"TP02013"
    ,"03-08-90"
    ,"3M"
    ,"aka TOUR OF HELL"
    , JAP
   },
    {//ROM NUMBER 174
    0X0038B5B5    ,"MAHJONG GOKU SPECIAL - SUNSOFT"
    ,"SS90002"
    ,"10-08-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 175
    0X2E955051    ,"SEKIKEHARA - TONKIN HOUSE"
    ,"TON90002"
    ,"14-09-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 176
    0XA326334A    ,"DAICHIKUN CRISIS DO NATURAL - SALIO"
    ,"SL01001"
    ,"22-11-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 177
    0XC2D2B823    ,"UNKNOWN GAME"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 178
    0XFBA3A1A4    ,"NAXAT STADIUM - TAISANG VERSION"
    ,"NX90006"
    ,"26-10-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 179
    0XA6539306    ,"KATTOBI! TAKUHAI-KUN - TONKIN HOUSE"
    ,"TON90004"
    ,"09-11-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 180
    0X73593F61    ,"UNKNOWN GAME"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 181
    0XE6C93AE7    ,"MAKAI PRINCE DORABO-CHAN - NAXAT SOFT"
    ,"NX90007"
    ,"21-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 182
    0X4D3B0BC9    ,"OBOCCHAMA KUN - NAMCO"
    ,"NC91001"
    ,"15-03-91"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 183
    0X82DEF9EE    ,"NIKO NIKO PUN - KSS"
    ,"NV91001"
    ,"13-12-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 184
    0X9EC6FC6C    ,"IDOL HANAFUDA FAN CLUB - GAMES EXPRESS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 185
    0X2546EFE0    ,"MORITA SHOGI PC - RANDOM HOUSE"
    ,"NAPH-1021"
    ,"27-09-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 186
    0XA32430D5    ,"NHK TAIGA DRAMA TAIHEIKI - NHK"
    ,"NV92001"
    ,"31-01-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 187
    0X951ED380    ,"CHIBI MARUKO-CHAN QUIZ DE PIHYARA - NAMCO"
    ,"NC92001"
    ,"10-01-92"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 188
    0X4148FD7C    ,"PACHIOKUN JUBAN SHOBU - COCONUTS"
    ,"CJ92002"
    ,"13-03-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 189
    0XF2285C6D    ,"NAXAT SOCCER"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 190
    0X02DDE03E    ,"KIYUU KIYOKU MAHJONG IDOL GRAPHICS - GAMES EXPRESS"
    ,"T4955754200915"
    ,""
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 191
    0X4052FFAB    ,"UNKNOWN GAME"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 192
    0XB01EE703    ,"HONO NO TATAKA TAMAKO DODGE DANPEI - HUDSON"
    ,"HC92059"
    ,"25-09-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 193
    0X0AA88F33    ,"PC PACHISLOT IDOL GAMBLER - GAMES EXPRESS"
    ,"T4955754200939"
    ,""
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 194
    0XB866D282    ,"AV POKER WORLD GAMBLER - GAMES EXPRESS"
    ,"T4955754200946"
    ,""
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 195
    0XE5B6B3E5    ,"KIYUU KIYOKU MAHJONG IDOL GRAPHICS 2 - GAMES EXPRESS"
    ,"T4955754200977"
    ,""
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 196
    0X85A1E7B6    ,"FORMATION SOCCER HUMAN CUP '90 - HUMAN"
    ,"HM90003"
    ,"27-04-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 197
    0X7146027C    ,"FORMATION SOCCER ON J.LEAGUE - HUMAN"
    ,"HM94007"
    ,"15-01-94"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 198
    0XD5CE2D5F    ,"SUPER MOMO TAROU DENSETSU - HUDSON"
    ,"HC89021"
    ,"15-09-89"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 199
    0X1555697E    ,"SUPER MOMO TAROU DENTETSU II - SUMMER PROJECT"
    ,"HC91050"
    ,"20-12-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 200
    0X7B96317C    ,"MOMO TAROU DENSETSU TURBO - HUDSON"
    ,"HC90034"
    ,"20-07-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 201
    0X345F43E9    ,"MOMO TAROU KATSU GEKI - HUDSON"
    ,"HC90031"
    ,"21-09-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 202
    0XF860455C    ,"MOMO TAROU DENSETSU GAIDEN - SUMMER PROJECT"
    ,"HC92060"
    ,"04-12-92"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 203
    0X6CCA614C    ,"MOMO TAROU DENTETSU II - HUDSON"
    ,"HC90040"
    ,"22-12-90"
    ,"6M"
    ,""
    , JAP
   },
    {//ROM NUMBER 204
    0X19FF94E5    ,"GOKURAKU CHUKA TAISEN - TAITO"
    ,"TP03021"
    ,"13-03-92"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 205
    0XE749A22C    ,"GOKURAKU CHUKA TAISEN - TAITO 384K STYLE"
    ,"TP03021"
    ,"13-03-92"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 206
    0XE87190F1    ,"MESOPOTAMIA - ATLUS"
    ,"AT03001"
    ,"04-10-91"
    ,"4M"
    ,"aka SOMER ASSAULT, 1p"
    , JAP
   },
    {//ROM NUMBER 207
    0XF0227837    ,"SOMER ASSAULT - ATLUS"
    ,"TGX040089"
    ,""
    ,"4M"
    ,"aka MESOPOTAMIA"
    , USA
   },
    {//ROM NUMBER 208
    0X767245CD    ,"CHINA WARRIOR - HUDSON"
    ,"TGX020008"
    ,""
    ,"2M"
    ,"aka THE KUNG FU, 1p"
    , USA
   },
    {//ROM NUMBER 209
    0XDC268242    ,"CHINA WARRIOR - NEC"
    ,"TGX020008"
    ,""
    ,"2M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 210
    0XB552C906    ,"CHINA WARRIOR - NEC"
    ,"TGX020008"
    ,""
    ,"2M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 211
    0X5D0E3105    ,"SUPER STAR SOLDIER - HUDSON"
    ,"HE-1097"
    ,"06-07-90"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 212
    0XAB3C5804    ,"SUPER STAR SOLDIER - HUDSON"
    ,"HE-1097"
    ,"06-07-90"
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 213
    0X82AE3B16    ,"TORA E NO MICHI - CAPCOM"
    ,"JC63004"
    ,"23-02-90"
    ,""
    ,"aka TIGER ROAD"
    , JAP
   },
    {//ROM NUMBER 214
    0XBF797067    ,"TORA E NO MICHI - CAPCOM"
    ,"JC63004"
    ,"23-02-90"
    ,""
    ,"aka TIGER ROAD"
    , JAP
   },
    {//ROM NUMBER 215
    0X9E86FFB0    ,"DOUBLE DUNGEONS - MASYNYA"
    ,"NCS89006"
    ,"29-09-89"
    ,"2M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 216
    0X86087B39    ,"DOUBLE DUNGEONS - MASYNYA"
    ,"NCS89006"
    ,"29-09-89"
    ,"2M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 217
    0XDB872A64    ,"KLAX - TENGEN"
    ,"TTGX20001"
    ,""
    ,"2M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 218
    0XC74FFBC9    ,"KLAX - TENGEN"
    ,"TG90001"
    ,"10-08-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 219
    0X8DC0D85F    ,"CADASH - TAITO"
    ,"TP02015"
    ,"18-01-91"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 220
    0X7D48D2FC    ,"CADASH - TAITO"
    ,"TP02015"
    ,"18-01-91"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 221
    0X9EDC0AEA    ,"CHAMPION WRESTLER - TAITO"
    ,"TPO2014"
    ,"14-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 222
    0X76164593    ,"CHAMPION WRESTLER - TAITO"
    ,"TP02014"
    ,"14-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 223
    0X69180984    ,"POWER LEAGUE BASEBALL"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 224
    0XD329CF9A    ,"POWER LEAGUE II - HUDSON"
    ,"HC89020"
    ,"08-08-89"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 225
    0XD3FD6971    ,"POWER LEAGUE III - HUDSON"
    ,"HC90037"
    ,"10-08-90"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 226
    0X30CC3563    ,"POWER LEAGUE IV - HUDSON"
    ,"HC91046"
    ,"09-08-91"
    ,"4M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 227
    0XBB654D1C    ,"POWER LEAGUE V - HUDSON"
    ,"HC92057"
    ,"07-08-92"
    ,"6M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 228
    0X66B167A9    ,"BASEBALL91"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 229
    0X44F60137    ,"COLLEGE PRO BASEBALL '89 - INTEC"
    ,"IG89002"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 230
    0X1772B229    ,"COLLEGE PRO BASEBALL '90 - INTEC"
    ,"IG90001"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 231
    0X951AA310    ,"WORLD CLASS BASEBALL - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 232
    0X9693D259    ,"BALLISTIX - PSYGNOSYS"
    ,"CJ0001"
    ,"13-12-91"
    ,"2M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 233
    0X8ACFC8AA    ,"BALLISTIX - PSYGNOSIS"
    ,""
    ,""
    ,"2M"
    ,"2p"
   },
    {//ROM NUMBER 234
    0X57615647    ,"SHOCKMAN - NCS"
    ,"TGX040087"
    ,""
    ,"4M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 235
    0X109BA474    ,"KAIZOU NINGEN SHUBIBIMAN 2 - MASYNYA"
    ,"NCS91001"
    ,"27-04-91"
    ,"4M"
    ,"aka SHOCKMAN, 2p"
    , JAP
   },
    {//ROM NUMBER 236
    0XCA68FF21    ,"ENERGY - MASYNYA"
    ,"NCS89005"
    ,"19-04-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 237
    0XDD1D1035    ,"ENERGY - MASYNYA"
    ,"NCS89005"
    ,"19-04-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 238
    0XA98D276A    ,"CYBER CORE - IGS"
    ,"TGX030030"
    ,""
    ,"3M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 239
    0XA0C97557    ,"CYBER CORE - IGS"
    ,"AI-02001"
    ,"09-03-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 240
    0XD0C250CA    ,"CYBER CROSS - FACE"
    ,"FA01-002"
    ,"23-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 241
    0XDCD3E602    ,"CYBER CROSS - FACE"
    ,"FA01-002"
    ,"23-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 242
    0X07BC34DC    ,"SAMURAI-GHOST - NAMCO"
    ,"TGX040085"
    ,""
    ,"4M"
    ,"aka GENPEI TORAMADEN VOLUME 2, 1p"
    , USA
   },
    {//ROM NUMBER 243
    0X8793758C    ,"GENPEI TORAMADEN 2 - NAMCO"
    ,"NC92002"
    ,"07-04-92"
    ,"4M"
    ,"aka Samurai Ghost, 1p"
    , JAP
   },
    {//ROM NUMBER 244
    0X1EB30EEB    ,"FIRE PRO WRESTLING - HUMAN"
    ,"HM89001"
    ,"22-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 245
    0X90ED6575    ,"FIRE PRO WRESTLING - HUMAN"
    ,"HM89001"
    ,"22-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 246
    0XA17D4D7E    ,"GUNHED - HUDSON"
    ,"HC89019"
    ,"07-07-89"
    ,"3M"
    ,"aka BLAZING LAZERS, 1p"
    , JAP
   },
    {//ROM NUMBER 247
    0X113DD5F0    ,"GUNHED - HUDSON"
    ,"HC89019"
    ,"07-07-89"
    ,"3M"
    ,"aka BLAZING LAZERS, 1p"
    , JAP
   },
    {//ROM NUMBER 248
    0X7AA9D4DC    ,"BLAZING LAZERS - HUDSON"
    ,"TGX030010"
    ,""
    ,"3M"
    ,"aka GUNHED, 1p"
    , USA
   },
    {//ROM NUMBER 249
    0X3B3808BD    ,"TENNOKOE MEMORY BANK - HUDSON"
    ,""
    ,""
    ,""
    ,"EXTRA SAVE RAM THING BY HUDSON"
    , JAP
   },
    {//ROM NUMBER 250
    0X51A12D90    ,"GAMES EXPRESS CD CARD 1993"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 251
    0X3F9F95A4    ,"CD-ROM SYSTEM VER. 1.00 - NEC"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 252
    0XD634D931    ,"CD-ROM SYSTEM VER. 2.00 - NEC"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 253
    0X283B74E0    ,"CD-ROM SYSTEM VER. 2.10 - NEC"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 254
    0XDD35451D    ,"SUPER CD-ROM2 SYSTEM VER. 3.00 - NEC"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 255
    0XE6F16616    ,"SUPER CD-ROM2 SYSTEM VER. 3.00 - NEC"
    ,"PCE-SC1"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 256
    0XF42AA73E    ,"DON DOKO DON - TAITO"
    ,"TP02010"
    ,"31-05-90"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 257
    0X633A3D48    ,"DON DOKO DON - TAITO"
    ,"TP02010"
    ,"31-05-90"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 258
    0XBB761F3B    ,"HANI ON THE ROAD - FACE"
    ,"FA02-006"
    ,"07-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 259
    0X9897FA86    ,"HANI ON THE ROAD - FACE"
    ,"FA02-006"
    ,"07-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 260
    0X348022F7    ,"JJ & JEFF - HUDSON"
    ,"TGX020014"
    ,""
    ,"2M"
    ,"aka KATO & KEN CHAN"
    , USA
   },
    {//ROM NUMBER 261
    0X6069C5E7    ,"KATO & KEN  CHAN - HUDSON"
    ,"HC62006"
    ,"30-11-87"
    ,"2M"
    ,"aka JJ & JEFF"
    , JAP
   },
    {//ROM NUMBER 262
    0X88796264    ,"CHEW MAN FU - HUDSON"
    ,"TGX020035"
    ,""
    ,"2M"
    ,"aka BE BALL, 2p"
    , USA
   },
    {//ROM NUMBER 263
    0XE439F299    ,"BE BALL - HUDSON"
    ,"HC90028"
    ,"30-03-90"
    ,"2M"
    ,"aka CHEW-MAN-FU, 2p"
    , JAP
   },
    {//ROM NUMBER 264
    0X261F1013    ,"BE BALL - HUDSON"
    ,"HC90028"
    ,"30-03-90"
    ,"2M"
    ,"aka CHEW-MAN-FU, 2p"
    , JAP
   },
    {//ROM NUMBER 265
    0X0B7F6E5F    ,"MOTO ROADER II - MASYNYA"
    ,"NCS91002"
    ,"29-03-91"
    ,"3M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 266
    0X364508DA    ,"MOTO ROADER II - MASYNYA"
    ,"NCS91002"
    ,"29-03-91"
    ,"3M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 267
    0X745408AE    ,"MOTO ROADER - MASYNYA"
    ,"NCS89002"
    ,"23-02-89"
    ,"2M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 268
    0X428F36CD    ,"MOTO ROADER - MASYNYA"
    ,"NCS89002"
    ,"23-02-89"
    ,"2M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 269
    0X13BF0409    ,"F1 TRIPLE BATTLE - HUMAN"
    ,"HM89002"
    ,"23-12-89"
    ,"3M"
    ,""
	 ,TWO_PART_ROM
      | JAP
   },
    {//ROM NUMBER 270
    0XB9DFC085    ,"F1 TRIPLE BATTLE - HUMAN"
    ,"HM89002"
    ,"23-12-89"
    ,"3M"
    ,""
	 ,TWO_PART_ROM
      | JAP
   },
    {//ROM NUMBER 271
    0X020DC2DF    ,"F1 PILOT - PACK-IN-VIDEO"
    ,"PV1001"
    ,"23-03-89"
    ,""
    ,"3M"
    , JAP
   },
    {//ROM NUMBER 272
    0X09048174    ,"F1 PILOT - PACK-IN-VIDEO"
    ,"PV1001"
    ,"23-03-89"
    ,""
    ,"3M"
    , JAP
   },
    {//ROM NUMBER 273
    0X3E647D8B    ,"POWER ELEVEN - HUDSON"
    ,"HC91039"
    ,"21-06-91"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 274
    0X21B5409C    ,"POWER ELEVEN - HUDSON"
    ,"HC91039"
    ,"21-06-91"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 275
    0X72E00BC4    ,"TOWER OF DRUAGA, THE - NAMCO"
    ,"NC92003"
    ,"25-06-92"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 276
    0X8A046CDC    ,"TOWER OF DRUAGA, THE - NAMCO"
    ,"NC92003"
    ,"25-06-92"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 277
    0XE8702D51    ,"PHOTOGRAPH BOY - IREM"
    ,"IC04007"
    ,"02-10-92"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 278
    0XDFD4593A    ,"PHOTOGRAPH BOY - IREM"
    ,"IC04007"
    ,"02-10-92"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 279
    0XC90971BA    ,"FINAL BLASTER - NAMCO"
    ,"NC90007"
    ,"28-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 280
    0XB9899178    ,"FINAL BLASTER - NAMCO"
    ,"NC90007"
    ,"28-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 281
    0XB18D102D    ,"ETERNAL CITY TOSHI TENSO KEIKAKU - NAXAT"
    ,"NX91003"
    ,"12-04-91"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 282
    0X74903426    ,"ETERNAL CITY TOSHI TENSO KEIKAKU - NAXAT"
    ,"NX91003"
    ,"12-04-91"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 283
    0XF91B055F    ,"CITY HUNTER - SUNSOFT"
    ,"SS90001"
    ,"02-03-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 284
    0XDF804DC7    ,"CITY HUNTER - SUNSOFT"
    ,"SS90001"
    ,"02-03-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 285
    0X44AF9BEA    ,"CRATERMAZE - HUDSON"
    ,"TGX020027"
    ,""
    ,"2M"
    ,"aka DORAEMON MEIKYU DAISAKUSEN, 1p"
    , USA
   },
    {//ROM NUMBER 286
    0XDC760A07    ,"DORAEMON MEIKYU DAISAKUSEN - HUDSON"
    ,"HC89023"
    ,"31-10-89"
    ,"2M"
    ,"aka CRATERMAZE, 1p"
    , JAP
   },
    {//ROM NUMBER 287
    0X04188C5C    ,"VEIGUES TACTICAL GLADIATOR - VICTOR"
    ,"JC63005"
    ,"29-06-90"
    ,"3M"
    ,"3p"
    , JAP
   },
    {//ROM NUMBER 288
    0XF46298E3    ,"VEIGUES TACTICAL GLADIATOR - VICTOR"
    ,"JC63005"
    ,"29-06-90"
    ,"3M"
    ,"3p"
    , JAP
   },
    {//ROM NUMBER 289
    0XAD6E0376    ,"VEIGUES TACTICAL GLADIATOR - VICTOR"
    ,""
    ,""
    ,"3M"
    ,"3p"
    , USA
   },
    {//ROM NUMBER 290
    0X96E0CD9D    ,"NINJA WARRIORS, THE - TAITO"
    ,"TP01002"
    ,"30-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 291
    0X62654AD5    ,"NINJA WARRIORS, THE - TAITO"
    ,"TPO1002"
    ,"30-06-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 292
    0X462256FB    ,"ROCK ON - BIGCLUB"
    ,"BG01004"
    ,"22-08-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 293
    0X2FD65312    ,"ROCK ON - BIGCLUB"
    ,"BG01004"
    ,"22-08-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 294
    0XBE990010    ,"W RING THE DOUBLE RINGS - NAXAT"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 295
    0X83213ADE    ,"W RING THE DOUBLE RINGS - NAXAT"
    ,"NX90005"
    ,"28-09-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 296
    0X1A8393C6    ,"GALAGA '88 - NAMCO"
    ,"NC63002"
    ,"15-07-88"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 297
    0X6273A9D4    ,"GALAGA '90 - NAMCO"
    ,"TGX020018"
    ,""
    ,"2M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 298
    0XCE2E4F9F    ,"SUPER VOLLEY BALL - VIDEO SYSTEM"
    ,"VS-90002"
    ,"07-02-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 299
    0X09CBB5E6    ,"SUPER VOLLEY BALL - VIDEO SYSTEM"
    ,"VS-90002"
    ,"07-02-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 300
    0X23D22D63    ,"SONIC SPIKE - IGS"
    ,"ITGX10001"
    ,""
    ,"2M"
    ,"aka WORLD BEACH VOLLEYBALL, 4p"
    , USA
   },
    {//ROM NUMBER 301
    0XBE850530    ,"WORLD BEACH VOLLEY - IGS"
    ,""
    ,"27-07-90"
    ,"2M"
    ,"aka SONIC SPIKE"
    , JAP
   },
    {//ROM NUMBER 302
    0XAD226F30    ,"VOLFIELD - TAITO"
    ,"TP01005"
    ,"27-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 303
    0X94C55627    ,"VOLFIED - TAITO"
    ,"TP01005"
    ,"27-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 304
    0X87FD22AD    ,"BOMBERMAN - HUDSON"
    ,"HC90036"
    ,"07-12-90"
    ,"2M"
    ,"5p, linkable"
   },
    {//ROM NUMBER 305
    0X9ABB4D1F    ,"BOMBERMAN - HUDSON"
    ,"HC90036"
    ,"07-12-90"
    ,"2M"
    ,"5p, linkable"
    , JAP
   },
    {//ROM NUMBER 306
    0XB300C5D0    ,"BOMBERMAN '93 - HUDSON"
    ,"HC92061"
    ,"11-12-92"
    ,"4M"
    ,"5p, linkable"
    , JAP
   },
    {//ROM NUMBER 307
    0X05362516    ,"BOMBERMAN '94 - HUDSON"
    ,"HC93065"
    ,"10-12-93"
    ,"8M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 308
    0X2CB5CD55    ,"PC GENJIN - HUDSON"
    ,"HC89024"
    ,"15-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 309
    0XB630AB25    ,"PC GENJIN - HUDSON"
    ,"HC89024"
    ,"15-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 310
    0X2CB796E2    ,"PC GENJIN - HUDSON"
    ,"HC89024"
    ,"15-12-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 311
    0X3028F7CA    ,"PC GENJIN 2 - HUDSON"
    ,"HC91043"
    ,"19-07-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 312
    0XA170B60E    ,"PC GENJIN 3 - HUDSON"
    ,"HC93063"
    ,"02-04-93"
    ,"8M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 313
    0XD5C782F2    ,"BONK'S ADVENTURE - HUDSON"
    ,""
    ,""
    ,""
    ,"1p"
    , USA
   },
    {//ROM NUMBER 314
    0X64301FF1    ,"BONK'S REVENGE - HUDSON"
    ,"TGX040058"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 315
    0X9913A9DE    ,"BONK 3 BONK'S BIG ADVENTURE - HUDSON"
    ,"TGX080097"
    ,""
    ,"8M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 316
    0XEB923DE5    ,"HEAVY UNIT - TAITO"
    ,"TP01004"
    ,"22-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 317
    0XCAAD79CE    ,"HEAVY UNIT - TAITO"
    ,"TP01004"
    ,"22-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 318
    0X60ECAE22    ,"NAXAT OPEN - NAXAT"
    ,"NX89001"
    ,"30-05-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 319
    0X31DD1C32    ,"NAXAT OPEN - NAXAT"
    ,"NX89001"
    ,"30-05-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 320
    0X2E5AC9C0    ,"BOXY BOY - MEDIA RINGS"
    ,"TGX010031"
    ,""
    ,"1M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 321
    0XFB37DDC4    ,"BOXY BOY - MEDIA RINGS"
    ,""
    ,""
    ,""
    ,"aka SOHKO BAN WORLD"
    , JAP
   },
    {//ROM NUMBER 322
    0X2F8935AA    ,"MAJIN EIYU WATARU - HUDSON"
    ,"HC63012"
    ,"30-08-88"
    ,"2M"
    ,"aka KEITH COURAGE IN ALPHA ZONES"
    , JAP
   },
    {//ROM NUMBER 323
    0XB54DEBD1    ,"KEITH COURAGE IN ALPHA ZONES - SUNRISE"
    ,"TGX020001"
    ,""
    ,"2M"
    ,"aka MAJIN EIYU WATARU, 1p"
    , USA
   },
    {//ROM NUMBER 324
    0XB77F2E2F    ,"ZERO 4 CHAMP - MEDIA RINGS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 325
    0XEE156721    ,"ZERO 4 CHAMP - MEDIA RINGS"
    ,"MR91003"
    ,"08-03-91"
    ,""
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 326
    0X5C4D1991    ,"BULLFIGHT RING NO HAJA - CREAM"
    ,"CC-01001"
    ,"08-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 327
    0X3E4EAF98    ,"BULLFIGHT RING NO HAJA - CREAM"
    ,"CC-01001"
    ,"08-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 328
    0X8E4D75A8    ,"NEW ZEALAND STORY, THE - TAITO"
    ,"TP02007"
    ,"23-02-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 329
    0X1772A6BC    ,"NEW ZEALAND STORY, THE - TAITO"
    ,"TP02007"
    ,"23-02-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 330
    0XB01F70C2    ,"NARAZUMO NO SENTOU BUTAI BLOODY WOLF - DATA EAST"
    ,"DE89003"
    ,"01-09-89"
    ,""
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 331
    0X47AFE6D7    ,"BLOODY WOLF - DATA EAST"
    ,"TGX040037"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 332
    0X99033916    ,"TOILET KIDS - MEDIA RINGS"
    ,"MR92005"
    ,"06-03-92"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 333
    0X53B7784B    ,"TOILET KIDS - MEDIA RINGS"
    ,""
    ,"06-03-92"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 334
    0XB64DE6FD    ,"ALIEN CRUSH - NAXAT"
    ,""
    ,""
    ,"2M"
    ,""
	 ,PINBALL_KEY
      | USA
   },
    {//ROM NUMBER 335
    0X60EDF4E1    ,"ALIEN CRUSH - NAXAT"
    ,"NX63001"
    ,"14-09-88"
    ,"2M"
    ,""
	 ,PINBALL_KEY
      | JAP
   },
    {//ROM NUMBER 336
    0X2762792B    ,"DEVIL'S CRUSH - NAXAT"
    ,""
    ,""
    ,"3M"
    ,"2p"
	 ,TWO_PART_ROM | PINBALL_KEY
      | USA
   },
    {//ROM NUMBER 337
    0X166A0E44    ,"DEVIL'S CRASH - NAXAT"
    ,"NX90004"
    ,"20-07-90"
    ,"3M"
    ,"2p"
	 ,TWO_PART_ROM | PINBALL_KEY
      | JAP
   },
    {//ROM NUMBER 338
    0XD233C05A    ,"BURNING ANGEL - NAXAT"
    ,"NX90008"
    ,"07-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 339
    0X17A47D0D    ,"BURNING ANGEL - NAXAT"
    ,"NX90008"
    ,"07-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 340
    0X033E8C4A    ,"CHASE HQ - TAITO"
    ,"TP02006"
    ,"26-01-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 341
    0X6F4FD790    ,"CHASE HQ - TAITO"
    ,"TP02006"
    ,"26-01-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 342
    0XD6FC51CE    ,"STRIP FIGHTER II - GAMES EXPRESS"
    ,"T4955754200984"
    ,""
    ,"8M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 343
    0X5F2C9A45    ,"STRIP FIGHTER II - GAMES EXPRESS"
    ,"T4955754200984"
    ,""
    ,"8M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 344
    0X85AA49D0    ,"SINISTRON - IGS"
    ,"ITGX10007"
    ,""
    ,"4M"
    ,"aka VIOLENT SOLDIER"
    , JAP
   },
    {//ROM NUMBER 345
    0X1BC36B36    ,"VIOLENT SOLDIER - IGS"
    ,"AI02005"
    ,"14-12-90"
    ,"3M"
    ,"aka SINISTRON, 1p"
    , JAP
   },
    {//ROM NUMBER 346
    0X34FD4EF2    ,"VIOLENT SOLDIER - IGS"
    ,"AI02005"
    ,"14-12-90"
    ,"3M"
    ,"aka SINISTRON, 1p"
    , JAP
   },
    {//ROM NUMBER 347
    0X70D90E20    ,"WORLD COURT TENNIS - NAMCO"
    ,"TGX020019"
    ,""
    ,"2M"
    ,"4p"
    , USA
   },
    {//ROM NUMBER 348
    0X11A36745    ,"WORLD COURT TENNIS - NAMCO"
    ,"NC63004"
    ,"11-08-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 349
    0XDCA24A76    ,"FANTASY ZONE - SEGA"
    ,"H49G-1001"
    ,"14-10-88"
    ,"2M"
    ,""
    , USA
   },
    {//ROM NUMBER 350
    0X72CB0F9D    ,"FANTASY ZONE - SEGA"
    ,"H49G-1001"
    ,"14-10-88"
    ,"2M"
    ,""
   },
    {//ROM NUMBER 351
    0X05453628    ,"ALICE IN WONDERDREAM - FACE"
    ,"FA02-007"
    ,"07-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 352
    0X12C4E6FD    ,"ALICE IN WONDERDREAM - FACE"
    ,"FA02-007"
    ,"07-12-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 353
    0XA9A94E1B    ,"NEUTOPIA - HUDSON V1"
    ,""
    ,""
    ,"3M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 354
    0X30D4BD0E    ,"NEUTOPIA - HUDSON V2"
    ,""
    ,""
    ,"3M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 355
    0X9D1A0F5A    ,"NEUTOPIA - HUDSON V1"
    ,"HC89022"
    ,"17-11-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 356
    0X9C49EF11    ,"NEUTOPIA - HUDSON V2"
    ,"HC89022"
    ,"17-11-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 357
    0XAE26F30F    ,"NEUTOPIA II - HUDSON"
    ,"TGX060078"
    ,""
    ,"6M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 358
    0XF0AB946E    ,"NEUTOPIA II - HUDSON V1"
    ,"HC91047"
    ,"27-09-91"
    ,"6M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 359
    0X2B94AEDC    ,"NEUTOPIA II - HUDSON V2"
    ,"HC91047"
    ,"27-09-91"
    ,"6M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 360
    0X595BB22A    ,"NECTARIS - HUDSON"
    ,"HC63016"
    ,"09-02-89"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 361
    0X0243453B    ,"NECTARIS - HUDSON"
    ,"HC63016"
    ,"09-02-89"
    ,"3M"
    ,"aka MILITARY MADNESS, 2p"
    , JAP
   },
    {//ROM NUMBER 362
    0X93F316F7    ,"MILITARY MADNESS - HUDSON"
    ,"TGX030015"
    ,""
    ,"3M"
    ,"aka NECTARIS, 2p"
    , USA
   },
    {//ROM NUMBER 363
    0X106BB7B2    ,"BATMAN - SUNSOFT"
    ,"SS90003"
    ,"12-10-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 364
    0X92C919EA    ,"BATMAN - SUNSOFT"
    ,"SS90003"
    ,"12-10-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 365
    0X25DE250A    ,"AOI BLINK - HUDSON"
    ,"HC90030"
    ,"27-04-90"
    ,"3M"
    ,"aka BLUE BLINK"
    , JAP
   },
    {//ROM NUMBER 366
    0X08A09B9A    ,"AOI BLINK - HUDSON"
    ,"HC90030"
    ,"27-04-90"
    ,"3M"
    ,"aka BLUE BLINK"
    , JAP
   },
    {//ROM NUMBER 367
    0X79362389    ,"1943 KAI - CAPCOM"
    ,"NX91002"
    ,"22-03-91"
    ,"4M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 368
    0XFDE08D6D    ,"1943 KAI - NAXAT"
    ,"NX91002"
    ,"22-03-91"
    ,"4M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 369
    0X4BD38F17    ,"GOMOLA SPEED - UPL"
    ,"UP02002"
    ,"28-09-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 370
    0X6E297E49    ,"GOMOLA SPEED - UPL"
    ,"UP02002"
    ,"28-09-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 371
    0X00C38E69    ,"RASTAN SAGA II - TAITO"
    ,"TP02012"
    ,"06-07-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 372
    0X85B85FF9    ,"RASTAN SAGA II - TAITO"
    ,"TP02012"
    ,"06-07-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 373
    0X70749841    ,"TV SPORTS BASKETBALL - CINEMAWARE"
    ,""
    ,"29-04-93"
    ,""
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 374
    0X9A41C638    ,"TV SPORTS BASKETBALL - CINEMAWARE"
    ,""
    ,""
    ,""
    ,"5p"
    , USA
   },
    {//ROM NUMBER 375
    0XDA059C9B    ,"TV SPORTS FOOTBALL - VICTOR"
    ,"JC63008"
    ,"29-03-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 376
    0X968D908A    ,"TV SPORTS FOOTBALL - VICTOR"
    ,"JC63008"
    ,"29-03-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 377
    0XBB3CA04A    ,"BUBBLEGUM CRASH - ARTMIC"
    ,"NX91005"
    ,"06-12-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 378
    0X0D766139    ,"BUBBLEGUM CRASH - ARTMIC"
    ,"NX91005"
    ,"06-12-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 379
    0XFAE0FC60    ,"ORDER OF THE GRIFFON - SSL"
    ,"TGX040072"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 380
    0XCAE1F5DB    ,"ORDER OF THE GRIFFON - SSL"
    ,"TGX040072"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 381
    0X4CAA6BE9    ,"SILENT DEBUGGERS - DATA EAST"
    ,""
    ,""
    ,""
    ,"1p"
    , USA
   },
    {//ROM NUMBER 382
    0X616EA179    ,"SILENT DEBUGGERS - DATA EAST"
    ,"DE90004"
    ,"29-03-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 383
    0X9FB4DE48    ,"RACING SPIRITS - IREM"
    ,"ICO3006"
    ,"19-07-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 384
    0X3E79734C    ,"RACING SPIRITS - IREM"
    ,"ICO3006"
    ,"19-07-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 385
    0XAE9FE1AA    ,"NINJA SPIRIT - IREM"
    ,"TGX040050"
    ,""
    ,"4M"
    ,""
    , USA
   },
    {//ROM NUMBER 386
    0X0590A156    ,"NINJA SPIRIT - IREM"
    ,"IC02004"
    ,"06-07-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 387
    0XDCF3675C    ,"DRAGON SPIRIT - NAMCO"
    ,"NC63003"
    ,"26-12-88"
    ,"2M"
    ,""
    , USA
   },
    {//ROM NUMBER 388
    0X01A76935    ,"DRAGON SPIRIT - NAMCO"
    ,"NC63003"
    ,"26-12-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 389
    0X1E1D0319    ,"DARIUS PLUS - TAITO"
    ,"NAPH-1009"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 390
    0XBEBFE042    ,"DARIUS"
    ,""
    ,""
    ,""
    ,""
   },
    {//ROM NUMBER 391
    0XBC655CF3    ,"SHINOBI - ASMIK"
    ,"AS01001"
    ,"08-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 392
    0X471903C6    ,"SHINOBI - ASMIK"
    ,"AS01001"
    ,"08-12-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 393
    0XC8A412E1    ,"VIGILANTE - IREM"
    ,""
    ,""
    ,"3M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 394
    0XEB4E600B    ,"VIGILANTE - IREM"
    ,"IC63001"
    ,"14-01-89"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 395
    0XE4124FE0    ,"VIGILANTE - IREM"
    ,""
    ,""
    ,"3M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 396
    0XCACC06FB    ,"ANKOKO DENSETSU - ATLUS"
    ,"BG01003"
    ,"28-06-89"
    ,"4M"
    ,"aka LEGENDARY AXE II"
    , JAP
   },
    {//ROM NUMBER 397
    0X07A226FB    ,"LEGENDARY AXE, THE - NEC"
    ,"TGX020003"
    ,""
    ,"2M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 398
    0X088D896D    ,"LEGENDARY AXE II, THE - NEC"
    ,""
    ,""
    ,""
    ,"1p"
    , USA
   },
    {//ROM NUMBER 399
    0XCFCFC7BE    ,"FINAL LAP TWIN - NAMCO"
    ,"NC89003"
    ,"07-07-89"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 400
    0XC8C084E3    ,"FINAL LAP TWIN - NAMCO"
    ,"NC89003"
    ,"07-07-89"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 401
    0X854C37B3    ,"FINAL LAP TWIN - NAMCO"
    ,"NC89003"
    ,"07-07-89"
    ,"3M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 402
    0XCEC3D28A    ,"R TYPE I - IREM"
    ,"HC63007"
    ,"25-03-88"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 403
    0X149D0511    ,"R TYPE I - IREM"
    ,"HC63007"
    ,"25-03-88"
    ,"2M"
    ,"1p (BOOTLEG TRAINER VERSION)"
    , JAP
   },
    {//ROM NUMBER 404
    0XF207ECAE    ,"R TYPE II - IREM"
    ,"HC63009"
    ,"03-06-88"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 405
    0X98B03EC9    ,"R TYPE COMPLETE"
    ,""
    ,""
    ,""
    ,"CRACKED TO WORK ON JAP PC-E"
    , USA
   },
    {//ROM NUMBER 406
    0X9E2CF932    ,"R TYPE COMPLETE"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 407
    0XE6458212    ,"PARASOL STARS - TAITO"
    ,""
    ,""
    ,"3M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 408
    0X786D9BBD    ,"PARASOL STARS - TAITO"
    ,""
    ,""
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 409
    0X45885AFB    ,"PARASOL STARS - TAITO"
    ,""
    ,""
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 410
    0X51E86451    ,"PARASOL STARS - TAITO"
    ,""
    ,""
    ,"3M"
    ,"2p"
    , USA
   },
    {//ROM NUMBER 411
    0X1E2CBCF8    ,"DUNGEON EXPLORER"
    ,""
    ,""
    ,"3M"
    ,"5p"
    , USA
   },
    {//ROM NUMBER 412
    0XF79657DD    ,"DUNGEON EXPLORER - HUDSON"
    ,"HC63015"
    ,"04-03-89"
    ,"3M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 413
    0X1B1A80A2    ,"DUNGEON EXPLORER - ATLUS"
    ,"HC63015"
    ,"04-03-89"
    ,"3M"
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 414
    0X231B1535    ,"TATSUJIN - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 415
    0XA6088275    ,"TATSUJIN - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 416
    0X589D33EB    ,"KING OF CASINO - VICTOR"
    ,""
    ,""
    ,"2M"
    ,""
    , USA
   },
    {//ROM NUMBER 417
    0XE4B3415C    ,"KING OF CASINO - VICTOR"
    ,"JC63006"
    ,"30-03-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 418
    0XBF52788E    ,"KING OF CASINO - VICTOR"
    ,"JC63006"
    ,"30-03-90"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 419
    0X4938B8BB    ,"POPULOUS - HUDSON"
    ,"HC91041"
    ,"05-04-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 420
    0X31E2E7B6    ,"POPULOUS - HUDSON"
    ,"HC91041"
    ,"05-04-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 421
    0X850829F2    ,"RAIDEN - SEIBU KAIHATSU"
    ,"HC91049"
    ,"22-11-91"
    ,"6M"
    ,"1p"
   },
    {//ROM NUMBER 422
    0XC7847DF7    ,"RAIDEN - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 423
    0XB99A85B6    ,"RAIDEN - SEIBU KAIHATSU"
    ,"HC91049"
    ,"22-11-91"
    ,"6M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 424
    0X2841FD1E    ,"WONDERBOY IN MONSTERLAND - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 425
    0X02DB6FE5    ,"WONDERBOY IN MONSTERLAND - HUDSON"
    ,""
    ,""
    ,""
    ,""
	 , USA
   },
    {//ROM NUMBER 426
    0X38E2917D    ,"WONDERBOY IN MONSTERLAND - HUDSON"
    ,""
    ,""
    ,""
    ,""
	 , USA
   },
    {//ROM NUMBER 427
    0X72A2C22C    ,"BARI BARI DENSETSU - TAITO"
    ,"TP01003"
    ,"29-11-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 428
    0XC267E25D    ,"BARI BARI DENSETSU - TAITO"
    ,"TP01003"
    ,"29-11-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 429
    0XED3A71F8    ,"JACKIE CHAN'S ACTION KUNG FU - HUDSON"
    ,"TGX040079"
    ,""
    ,"4M"
    ,"1p"
    , USA
   },
    {//ROM NUMBER 430
    0XC6FA6373    ,"JACKIE CHAN ACTION KUNGFU - HUDSON"
    ,"HC90032"
    ,"18-01-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 431
    0X3920105A    ,"ANDRE PANZA KICK BOXING - NEC"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 432
    0X8F02FD20    ,"POWER GOLF - HUDSON"
    ,"HC89018"
    ,"25-05-89"
    ,""
    ,""
   },
    {//ROM NUMBER 433
    0XEA324F07    ,"POWER GOLF - HUDSON"
    ,"HC89018"
    ,"25-05-89"
    ,""
    ,""
   },
    {//ROM NUMBER 434
    0X7ACB60C8    ,"HIT THE ICE - TAITO"
    ,"TP03019"
    ,"20-09-91"
    ,"4M"
    ,"4p"
    , JAP
   },
    {//ROM NUMBER 435
    0X775BD3E1    ,"HIT THE ICE - TAITO"
    ,"TPO3019"
    ,"20-09-91"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 436
    0X805A34B9    ,"TV SPORTS ICE HOCKEY - VICTOR"
    ,"JC63013"
    ,"29-04-93"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 437
    0X4DF54B81    ,"TV SPORTS HOCKEY - NEC"
    ,"TGX030064"
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 438
    0X04BF5EAF    ,"TV SPORTS HOCKEY - NEC"
    ,"TGX030064"
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 439
    0X4CEF0456    ,"WALLABY!! - MASYNYA"
    ,"NCS90005"
    ,"14-12-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 440
    0X0112D0C7    ,"WALLABY!! - MASYNYA"
    ,"NCS90005"
    ,"14-12-90"
    ,"3M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 441
    0X958BCD09    ,"BLODIA - HUDSON"
    ,"HC90027"
    ,"23-03-90"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 442
    0X05A4B72E    ,"TIMEBALL - HUDSON"
    ,""
    ,""
    ,"2M"
    ,"1p (AKA BLODIA)"
    , USA
   },
    {//ROM NUMBER 443
    0X09509315    ,"TWIN COBRA - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 444
    0XA586D190    ,"TWIN COBRA - TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 445
    0X43EFC974    ,"PARANOIA - NAXAT"
    ,"NX90001"
    ,"01-03-90"
    ,"2M"
    ,"aka PSYCHOSIS, 2p"
    , JAP
   },
    {//ROM NUMBER 446
    0X9893E0E6    ,"PARANOIA - NAXAT"
    ,"NX90001"
    ,"01-03-90"
    ,"2M"
    ,"aka PSYCHOSIS, 2p"
    , JAP
   },
    {//ROM NUMBER 447
    0X73E994A0    ,"PARANOIA - NAXAT"
    ,"NX90001"
    ,"01-03-90"
    ,"2M"
    ,"aka PSYCHOSIS, 2p"
    , JAP
   },
    {//ROM NUMBER 448
    0X73614660    ,"21 EMON - NEC"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 449
    0X5E4FA713    ,"ARTIST TOOL - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 450
    0X320F5018    ,"TENNOKOE BANK"
    ,"HC692"
    ,"XX-XX-91"
    ,""
    ,"EXTRA BACKUP RAM CARD"
    , JAP
   },
    {//ROM NUMBER 451
    0X968770F6    ,"BE BALL - TAISANG VERSION"
    ,"HC90028"
    ,"30-03-90"
    ,"2M"
    ,"aka CHEW-MAN-FU, 2p"
    , JAP
   },
    {//ROM NUMBER 452
    0X6EAB778C    ,"R TYPE II - TAISANG VERSION"
    ,"HC63009"
    ,"03-06-88"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 453
    0X4F2BD39F    ,"HYPERDYNE SIDEARMS - TAISANG VERSION"
    ,"H54G-1004"
    ,"14-07-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 454
    0XDE963B7E    ,"HYPERDYNE SIDEARMS - MAGAE CHIP VERSION"
    ,"H54G-1004"
    ,"14-07-89"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 455
    0XB0BA689F    ,"DARIUS ALPHA - NEC AVENUE & TAITO"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 456
    0XE1A73797    ,"BENKEI - SUNSOFT"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 457
    0X02A578C5    ,"FINAL SOLDIER SPECIAL VERSION - HUDSON"
    ,""
    ,"XX-XX-91"
    ,"4M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 458
    0X57F183AE    ,"GUNHED SPECIAL VERSION - HUDSON"
    ,""
    ,"XX-XX-89"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 459
    0X95F90DEC    ,"GAI FLAME - MASYNYA & NCS"
    ,""
    ,"XX-XX-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 460
    0XCC799D92    ,"HATRIS - BULLET PROOF"
    ,"MC91002"
    ,"24-05-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 461
    0X8E71D4F3    ,"ADVENTURE ISLAND - HUDSON"
    ,""
    ,""
    ,""
    ,"aka DRAGON'S CURSE, 1p"
    , JAP
   },
    {//ROM NUMBER 462
    0X62EC2956    ,"WORLD COURT TENNIS - NAMCO"
    ,"NC63004"
    ,"11-08-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 463
    0XC4EB68A5    ,"WORLD COURT TENNIS - NAMCO"
    ,"NC63004"
    ,"11-08-88"
    ,"2M"
    ,""
    , JAP
   },
    {//ROM NUMBER 464
    0X0AD97B04    ,"J.LEAGUE GREATEST ELEVEN SOCCER - NIHON BUSSAN"
    ,""
    ,"XX-XX-93"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 465
    0X61B80005    ,"KNIGHT RIDER SPECIAL - PACK-IN-VIDEO"
    ,"PV1003"
    ,"22-12-89"
    ,"2M"
    ,"1p"
    , JAP
   },
    {//ROM NUMBER 466
    0XF8861456    ,"MAHJONG GOKU SPECIAL - SUNSOFT"
    ,"SS90002"
    ,"10-08-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 467
    0XB101B333    ,"MAKAIPRN? CRAZY PLATFORMER - NAXAT"
    ,"XX-XX-90"
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 468
    0X625221A6    ,"MOMO TAROU DENSETSU TURBO - HUDSON"
    ,"HC90034"
    ,"20-07-90"
    ,"3M"
    ,""
    , JAP
   },
    {//ROM NUMBER 469
    0XD9E1549A    ,"MOMO TAROU DENTETSU II - HUDSON"
    ,"HC90040"
    ,"22-12-90"
    ,"6M"
    ,""
    , JAP
   },
    {//ROM NUMBER 470
    0X0441D85A    ,"NAZONO??"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 471
    0X20A7D128    ,"NAXAT STADIUM - NAXAT"
    ,"NX90006"
    ,"26-10-90"
    ,"4M"
    ,""
    , JAP
   },
    {//ROM NUMBER 472
    0X52520BC6    ,"CD-ROM SYSTEM VER. 2.00 - NEC"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 473
    0X9759A20D    ,"SUPER CD-ROM2 SYSTEM VER. 3.00 - NEC"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 474
    0XC5FDFA89    ,"POWER LEAGUE II - HUDSON"
    ,"HC89020"
    ,"08-08-89"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 475
    0X8AA4B220    ,"POWER LEAGUE III - HUDSON"
    ,"HC90037"
    ,"10-08-90"
    ,"3M"
    ,"2p"
    , JAP
   },
    {//ROM NUMBER 476
    0X7D3E6F33    ,"POWER LEAGUE `93 - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 477
    0XFAA6E187    ,"PUZZLE BOY - TELENET"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 478
    0XF2E6856D    ,"QUIZTOKO - GAMES EXPRESS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 479
    0X2BC023FC    ,"SUPER MOMO TAROU DENTETSU II - SUMMER PROJECT"
    ,"HC91050"
    ,"20-12-91"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 480
    0X61A6E210    ,"TSUPPARI SUMO WRESTLING GAME - NAXAT"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 481
    0X10B60601    ,"TV SPORTS BASKETBALL - CINEMAWARE"
    ,""
    ,"29-04-93"
    ,""
    ,"5p"
    , JAP
   },
    {//ROM NUMBER 482
    0XE7529890    ,"TV SPORTS ICE HOCKEY - VICTOR"
    ,"JC63013"
    ,"29-04-93"
    ,""
    ,""
    , JAP
   },
    {//ROM NUMBER 483
    0X14DAF737    ,"TV SPORTS FOOTBALL - VICTOR"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 484
    0XF45AFBCA    ,"CADASH - TAITO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 485
    0X0258ACCB    ,"LEGEND OF HERO TONMA, THE - IREM"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 486
    0X6257CCE7    ,"SPACE HARRIER - NEC AVENUE"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 487
    0X756A1802    ,"NEW ADVENTURE ISLAND - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 488
    0X85CC9B60    ,"DEAD MOON - NATSUME"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 489
    0XC2287894    ,"DEEP BLUE - PACK-IN-VIDEO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 490
    0X390710EC    ,"CYBER CORE - IGS"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 491
    0XE84890A5    ,"CHASE HQ - TAITO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 492
    0X2BBF3090    ,"BRAVOMAN"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 493
    0X8BF34FFA    ,"BOMBERMAN - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 494
    0X26020C77    ,"BOMBERMAN `93 - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 495
    0XC02B1B59    ,"AERO BLASTERS - KANEKO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 496
    0X2A3E08E2    ,"DROP OFF - DATA EAST"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 497
    0X2739B927    ,"PAC LAND - NAMCO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 498
    0X72814ACB    ,"ORDYNE - NAMCO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 499
    0XC159761B    ,"NIGHT CREATURES - MANLEY & ASSOCIATES"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 500
    0XC81D0371    ,"PSYCHOSIS - NAXAT"
    ,""
    ,""
    ,""
    ,"aka PARANOIA"
    , USA
   },
    {//ROM NUMBER 501
    0X5157A395    ,"VICTORY RUN - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 502
    0X500472D4    ,"TIGER ROAD - CAPCOM"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 503
    0X9C7A8EE4    ,"TRICKY KICK - IGS"
    ,""
    ,""
    ,""
    ,"aka TRICKY"
    , USA
   },
    {//ROM NUMBER 504
    0X0C7627A9    ,"WORLD SPORTS COMPETITION"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 505
    0X4161F202    ,"WORLD WPORTS COMPETITION"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 506
    0XF0CC3363    ,"SUPER VOLLEY BALL - VIDEO SYSTEM"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 507
    0X72D6860B    ,"TIME CRUISE - FACE"
    ,""
    ,""
    ,""
    ,""
	 ,PINBALL_KEY
      | USA
   },
    {//ROM NUMBER 508
    0XA019B724    ,"SPLATTERHOUSE - NAMCO"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 509
    0X284EBE25    ,"SOLDIER BLADE - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 510
    0X05054F4F    ,"SIDEARMS - CAPCOM"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 511
    0XEB9452F0    ,"MOTO ROADER - MASYNYA"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 512
    0X93F05168    ,"POWER GOLF - HUDSON"
    ,""
    ,""
    ,""
    ,""
    , USA
   },
    {//ROM NUMBER 513
     0X574352C6   ,"CD ROM 2 SYSTEM 3.0 - NEC / HUDSON"
     ,""
     ,""
     ,"3M"
     ,""
    , USA
    },
    {//ROM NUMBER 514
     0X6A628982   ,"ALTERED BEAST - SEGA"
     ,""
     ,""
     ,"4M"
     ,""
    , JAP
    },
    {//ROM NUMBER 515
     0X4D344C8C   ,"WONDERBOY IN MONSTERLAND - HUDSON"
     ,""
     ,""
     ,"2M"
     ,""
    , JAP
    },
    {//ROM NUMBER 516
     0X9BB8D362   ,"JAMANOID - THE HU62680 TEAM"
     ,""
     ,""
     ,"1M"
     ,""
    , USA
    },
    {//ROM NUMBER 517
     0X67AEDE77   ,"WONDERBOY IN MONSTERLAND - HUDSON"
     ,""
     ,""
     ,"2M"
     ,""
    , USA
    },
    {//ROM NUMBER 518
     0X6976D5B3   ,"15 IN 1 MEGA-COLLECTION - IMAGE"
     ,"'92"
     ,""
     ,"2M"
     ,""
    , USA
    },
   {//ROM NUMBER 519
    0X6203DE23    ,"QUIZTOKO - GAMES EXPRESS"
    ,""
    ,""
    ,""
    ,""
    , JAP
   },
  {//ROM NUMBER 520
   0X7E3C367B   ,"KICKBALL - NCS"
   ,""
   ,"'90"
   ,""
   ,""
   , USA
   },
  {//ROM NUMBER 521
   0XE7738B25   ,"DRAGON SPIRIT - NAMCO"
   ,"NC63003"
   ,"26-12-1988"
   ,""
   ,""
   , USA
   },
  {//ROM NUMBER 522
   0XAC2D7094   ,"DUNGEON EXPLORER - ATLUS"
   ,""
   ,"'89"
   ,""
   ,""
   , USA
   },
  {//ROM NUMBER 523
   0XFA7E5D66   ,"SILENT DEBUGGERS - DATA EAST"
   ,""
   ,"'91"
   ,""
   ,""
   , USA
   },
  {//ROM NUMBER 524
   0X90E6BF49    ,"UNREADABLE TITLE - HUDSON"
   ,""
   ,"'88"
   ,""
   ,""
   , JAP
   },
  {//ROM NUMBER 525
   0XE13A6CE8   ,"BARI BARI DENSETSU - TAITO"
   ,"TP01003"
   ,"29-11-89"
   ,"5M"
   ,""
   , JAP
   }


}; */

#endif

unsigned long
filesize (FILE * F)
{
  unsigned long old_pos, end;
  fgetpos (F, (fpos_t *) &old_pos);
  fseek (F, 0, SEEK_END);
  fgetpos (F, (fpos_t *) &end);
  fseek (F, old_pos, SEEK_SET);
  return end;
}

/*

unsigned long pack_filesize(PACKFILE *F)
  {
   unsigned long old_pos,end;
   pack_ftell(F,(long*)&old_pos);

   end=old_pos;

   while (!pack_feof(F))
     {
      pack_getc(F);
      end++;
      }


   fseek(F,0,SEEK_END);
   fgetpos(F,(long*)&end);
   fseek(F,old_pos,SEEK_SET);
   return end;
   }
*/

UInt32 CRC_file (char *name)
{
  FILE *F = fopen (name, "rb");
  UChar *tmp_data;
  UInt32 taille, index, CRC = -1, true_size;

  if (!F)
    return -1;

  taille = filesize (F);
  true_size = taille & 0xFFFFF000;
  if (taille & 0x0FFF)
    {
      //fprintf(stderr,"HEADER OF 0X%X BYTES\n",taille & 0x0FFF);
      fseek (F, taille & 0x0FFF, SEEK_SET);
    }
  if (!(tmp_data = (unsigned char *) (malloc (true_size))))
    exit (-1);
  fread (tmp_data, true_size, 1, F);
  for (index = 0; index < true_size; index++)
    {
      tmp_data[index] ^= CRC;
      CRC >>= 8;
      CRC ^= TAB_CONST[tmp_data[index]];
    }
  free (tmp_data);
  CRC = ~CRC;
//      fprintf(stderr,"CRC = 0X%lX\n",CRC);
  fclose (F);
  return CRC;
}

static
void pce_build_romlist_fail(FILE *rlf, int entry)
{
  fprintf(stdout, "Error in entry %d of roms.db\n", entry + 1);
  pce_romlist_size = entry;
  fclose(rlf);
}


void pce_build_romlist(void)
{
  FILE *rlf;
  char rlf_path[PATH_MAX], line[MAX_INPUT];
  int i;

  snprintf(rlf_path, PATH_MAX, "%s/roms.db", short_exe_name);

  if ((rlf = fopen(rlf_path, "r")) == NULL)
  {
    perror("Couldn't open ~/.hugo/roms.db for reading");
    return;
  }

  if (fscanf(rlf, "%d\n", &pce_romlist_size) == EOF)
  {
    perror("Failed to read the numeric value heading roms.db");
    return;
  }

  if (pce_romlist_size < 1)
  {
    fprintf(stdout, "Invalid number of roms specified in roms.db (%d)\n", i);
    return;
  }

  pce_romlist = (struct pce_rom_info *) malloc(pce_romlist_size * sizeof(struct pce_rom_info));

  for (i = 0; i < pce_romlist_size; i++)
  {
    if (fscanf(rlf, "%lx\n", &pce_romlist[i].CRC) == EOF) {
      pce_build_romlist_fail(rlf, i);
      return;
    }

    if (fgets(line, MAX_INPUT, rlf) == NULL) {
      pce_build_romlist_fail(rlf, i);
      return;
    }
    pce_romlist[i].name = strdup(line);

    if (fgets(line, MAX_INPUT, rlf) == NULL) {
      pce_build_romlist_fail(rlf, i);
      return;
    }
    pce_romlist[i].producer = strdup(line);

    if (fgets(line, MAX_INPUT, rlf) == NULL) {
      pce_build_romlist_fail(rlf, i);
      return;
    }
    pce_romlist[i].date = strdup(line);

    if (fgets(line, MAX_INPUT, rlf) == NULL) {
      pce_build_romlist_fail(rlf, i);
      return;
    }
    pce_romlist[i].note = strdup(line);

    if (fscanf(rlf, "%d\n", &pce_romlist[i].flags) == EOF) {
      pce_build_romlist_fail(rlf, i);
      return;
    }
  }

  fclose(rlf);
}
