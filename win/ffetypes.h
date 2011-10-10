
typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

struct ffeRGB {
	u8 r, g, b;
};

struct ffeMatrix3x3 {
	int _11, _12, _13;
	int _21, _22, _23;
	int _31, _32, _33;
};

struct Point64 {
	s64 x;
	s64 y;
	s64 z;
};

struct Point32 {
	s32 x;
	s32 y;
	s32 z;
};

struct ScreenCoord_t {
	u16 x, y;
};

struct ShipDef_t {
    short ForwardThrust;		// 0x00
    short RearThrust;			// 0x02
    char  Gunmountings;			// 0x03
    char  FuelScoop;			// 0x04
    short Mass;					// 0x06
    short Capacity;				// 0x08
    short Price;				// 0x0a
    short Scale;				// 0x0c
    short Description;			// 0x0e
    short Crew;					// 0x10
    short Missiles;				// 0x12
    char  Drive;				// 0x14
    char  IntegralDrive;		// 0x15
    short EliteBonus;			// 0x17
    short frontMount_x, frontMount_y, frontMount_z;
    short backMount_x, backMount_y, backMount_z;
    short leftMount_x, leftMount_y, leftMount_z;
    short rightMount_x, rightMount_y, rightMount_z;
};


struct Model_t {
    unsigned short * Mesh_ptr;
    signed char *    Vertices_ptr;
    int              NumVertices;
    signed char *    Normals_ptr;
    int              NumNormals;
    int              Scale;
    int              Scale2;
    int              Radius;
    int              Primitives;
    char	         DefaultColorR;
	char	         DefaultColorG;
	char	         DefaultColorB;
    char             padding;
    int              field_28;
    int              field_2C;
    int              field_30;
    unsigned short * Collision_ptr;
    ShipDef_t *      Shipdef_ptr;
    int              DefaultCharacter;
    unsigned short * Character[1];
};

typedef union 
{
  struct {
	u16 time;					// FIRST GLOBAL VAR, starTime >> 10
	u16 landingState;			// VAR1:Starmap Display:10=Trade;80=Text; 
								// 0 < <0x20 is cargo type; & 1: landing gear down
	u32 unique_Id;				// also used for random seed
	u32 mass;					// mass (planets only?) ffp val
	u32 local_Startime;			// creation time, tics
	u32 local_Stardate;			// creation time, days (used for arrival/departure)
	union {
		// flying objects
		struct {
			u16 ScaledWord_B0;			// pitch rate	(x rotation)
			u16 ushort_B2;				// roll rate	(z rotation)
			u16 ushort_B4;				// yaw rate	(y rotation)
			u16 ushort_B6;				// x accel rate
			u16 ushort_B8;				// y accel rate
			u16 Current_Main_Thrust;	// z accel rate
			u16 Thrust_BC;				// main thruster accel
			u16 Thrust_BE;				// retro thruster accel
			u16 Thrust_C0;				// top thruster accel
			u16 Thrust_C2;				// bottom thruster accel
			u16 Max_Main_Thrust;		// right thruster accel
			u16 Thrust_C6;				// left thruster accel
			u32 equip;					// equipment flags
			u32 dam_equip;				// damaged equipment flags
			u8 drive;					// drive type
			u8 num_gunmountings;		// number of gun mountings
			u8 laser_front;				// front laser
			u8 laser_rear;				// rear laser
			u8 laser_top;				// top turret laser
			u8 laser_bottom;			// bottom turret laser
			u8 missiles[10];
			u16 shields;
			u16 max_shields;
		};
		// orbitals
		struct {
			u32	radius;
			u16	velocity_x;
			u16	velocity_y;
			u16	velocity_z;
			u32 angle_x;
			u32 angle_y;
			u32 angle_velocity;
			u16 eccentricity;
			u8 rotation_speed;
			u8 docking_state;
			u8 docking_obj_index;
			u8 sysval1;					// set to 0x3f sysobj val
			u16 orientation;
			u16 pads;					// number of pads for starport
			u8 docking_obj[8];			// first docked object index, starport only
			u16 traffic_control;
			u16 FOR_weighting;
			u16 sysval2;				// 0xce * 8 + 8
			u16 sysval3;				// 
			u16 temp;					// temp in kelvin <0x116 => wind
			u16 sysval4;
		};
	};
  };
  s16 raw[36];
} GlobalVars;

struct ModelInstance_t {
	ffeMatrix3x3 relMatrix;		// relative orientation
	u8 uchar_24;				// set to 3Ch?
	u8 uchar_25;				// global position valid flag
	Point64 pos;				// global position
	Point64 rel_pos;			// relative position
	u8 parent_index;			// Parent object of current
	u8 uchar_57;				// rotational FOR flag
	u8 uchar_58;				// global orientation valid flag
	u8 uchar_59;
	ffeMatrix3x3 globMatrix;	// global orientation 
	u32 model_scale;			// exponential scale val
	u32 model_num;				// model number
	u8 index;					// index of THIS object instance in list
	u8 ship_type;				// object control - 0x1 orbital, 0x3 player ship, 0xb AI ship
	u8 dist_cam;				// exponential distance from camera
	u8 uchar_89;				// undefined
	u8 dist_3face;				// exponential distance outside view
	u8 sleep;					// frames between updates - set with 0x8a value
	Point32 velocity;			// velocity vector, actual
	ScreenCoord_t screenpos;	// xy position on screen
	GlobalVars globalvars;
	u16 mass_x4;				// mass*4, used for damage
	u16 parent_model;			// HS cloud - parent model, also modified by firing laser 
	u16 laser_next_pulse;		// time to next pulse laser shot?
	u16 laser_temp;				// laser temperature
	u16 fract_vel_x;			// fractional vel x 
	u16 fract_vel_y;			// fractional vel y
	u16 fract_vel_z;			// fractional vel z
	u32 dest_system;			// destination system code
	u16 jump_range;				// max jump range
	u8 post_hs_ai;				// post-HS AI mode
	u8 filter;					// filter?
	u32 jump_time;				// jump time (tics >> 0x10)
	u8 dest_index;				// destination index
	u8 ai_mode;					// AI mode
	u8 target_index;			// nav target index - used for missile also enemy index for pirate groups
	u8 thrust_power;			// 0-2, depending on retro power
	u16 target_off_x;			// target x-offset, used for station/starport first pass
	u16 target_off_y;			// target y-offset
	u16 target_off_z;			// target z-offset
	u16 target_dir_x;			// target x-direction
	u16 target_dir_y;			// target y-direction
	u16 target_dir_z;			// target z-direction
	u16 dist_target;			// exponential distance to target (shift of dir vec)
	u16 autopilot_pitch;		// autopilot pitch (x rotation)
	u16 autopilot_roll;			// autopilot roll (z rotation)
	u16 autopilot_yaw;			// autopilot yaw (y rotation)
	u16 cargo_space;			// remaining internal capacity, AI only
	u8 object_type;				// 0xff if player, 0xfb pirate, 0xfe HS cloud, 01 esc. capsule
	u8 cargo_fuel;				// cargo fuel in tons - AI only
	u32 bounty;
	u32 fuel_tank;				// fuel tank - 0x20000000 = 1t
	u8 field_122[2];			// 2 dup(?)
	u8 name[20];				// 20 bytes
	u64 interract_radius;		// interaction radius
	u64 collision_radius;		// primary collision radius
	u32 physics_timeout;		// physics timeout
	u8 flags;					// flags
	u8 FOR_timeout;				// FOR update timeout
	u8 smoke_timeout;			// smoke timeout
	u8 ecm_timeout;				// ecm/bomb timeout
	u8 avoid_timeout;			// autopilot avoidance check timeout
	u8 laser_flags;				// laser flags
};

struct DrawMdl_t {
	Model_t* model3d;			// Pointer to actual 3D Model_t used
	Point32 pos;				// actual center position
	u8 uchar10;					// undefined
	u8 uchar11;					// undefined
	u8 uchar12;					// undefined
	u8 uchar13;					// undefined
	ffeMatrix3x3 rotMatrix;
	Point32 ldir;				// might be Lighting vector!
	u32 scale;
	Point32 Vector;
	s32 localvars[7];
	u32 lpExtraVertex_Center;
	u32 lpExtraVertex_0;		// ..for subobjects
	u32 lpExtraVertex_1;		// ..for subobjects
	u32 lpExtraVertex_2;		// ..for subobjects
	u32 lpExtraVertex_3;		// ..for subobjects
	ffeRGB rgb3array[8];
	ffeMatrix3x3 altMatrix;
	Point32 textPoint;
	u32 packedcolor;			// 0000:0R:GB (pos in color cube)
	u8 ucharD0;					// undefined
	u8 ucharD1;					// undefined
	u8 ucharD2;					// undefined
	u8 ucharD3;					// undefined
	u32 radius;					// Last actual (shifted) radius for single ball
	u8 ucharD8;					// undefined
	u8 ucharD9;					// undefined
	u8 ucharDA;					// undefined
	u8 ucharDB;					// undefined
	u8 ucharDC;					// undefined
	u8 ucharDD;					// undefined
	u8 ucharDE;					// undefined
	u8 ucharDF;					// undefined
	u8 ucharE0;					// undefined
	u8 ucharE1;					// undefined
	u8 ucharE2;					// undefined
	u8 ucharE3;					// undefined
	u8 ucharE4;					// undefined
	u8 ucharE5;					// undefined
	u8 ucharE6;					// undefined
	u8 ucharE7;					// undefined
	u8 ucharE8;					// undefined
	u8 ucharE9;					// undefined
	u8 ucharEA;					// undefined
	u8 ucharEB;					// undefined
	u8 ucharEC;					// undefined
	u8 ucharED;					// undefined
	u8 ucharEE;					// undefined
	u8 ucharEF;					// undefined
	u32 counter;				// holds current vertexcalc level
	ffeRGB localColor;
	u8 ucharF7;					// undefined
	u32 forceMirror;
	u32 forceMirror_alt;
	u8 uchar100;				// undefined
	u8 uchar101;				// undefined
	u8 uchar102;				// undefined
	u8 uchar103;				// undefined
	u32 field_104;
	ScreenCoord_t screenpos1;
	u32 field_10C;
	ScreenCoord_t screenpos2;
	u8* lpVertexCache;
	u32 field_118;				// current num of calc. normals?
	Point32 tempVector;			// Rotated normal value??
	u32 field_128;				// -1 if end drawing?
	u32 field_12C;
	u32 scale2;					// init to 0, for planets to Scale2
	Point32 lpos;				// light source position
	u8 uchar140;				// undefined
	u8 uchar141;				// undefined
	u8 uchar142;				// undefined
	u8 uchar143;				// undefined
	u8 uchar144;				// undefined
	u8 uchar145;				// undefined
	u8 uchar146;				// undefined
	u8 uchar147;				// undefined
	u32 actualScale;			// ..from Model_t
	ModelInstance_t* modelInstance;
	u8* ptr_ModelVertices;
	u8* ptr_ModelNormals;
	u8 uchar158;				// undefined
	u8 uchar159;				// undefined
	u8 uchar15A;				// undefined
	u8 uchar15B;				// undefined
};

//Equipment flags (0xc8 dword in PhysObj):
//
//0x1			laser cooling booster
//0x2			auto-refueller
//0x4			military camera
//0x8			escape capsule
//0x10		?energy bomb?
//0x20		navigation computer
//0x40		combat computer
//0x80		autotargeter
//0x100
//0x200		missile viewer
//0x400		cargo scoop
//0x800		chaff dispensor
//0x10000
//0x20000		cargo bay life support
//0x40000		scanner
//0x80000		ecm
//0x100000	fuel scoop
//0x200000	autopilot
//0x400000	radar mapper
//0x800000	naval ecm
//0x1000000	HS cloud analyser
//0x2000000
//0x4000000	energy bomb
//0x8000000	stowmaster
//0x10000000	energy booster
//0x20000000
//0x40000000	atmos. shield
//0x80000000	hull auto-repair system

// AI modes:
//
//0x0		Basic navigation mode
//0x1		Attacking - turning towards
//0x2		Attacking - firing
//0x3		Attacking - turning away
//0x4		Pirate interception
//0x5		Transitional state to 0x4
//0x6		Static?
//0x7		travel to HS entry point
//0x8 	HS exit routine
//0x9		Bounty hunter interception
//0xa		Patrol?
//0xb		Formation navigation
//0xc		Missile evasion?
//0xd		Auxiliary ships around station
//0xe
//0xf
//0x10
//0x11	Delayed HS exit cloud
//0x12	HS exit cloud
//0x13	Missile
//0x14	Mine
//0x15	Smoking cargo
//0x16	Normal cargo - abandoned ship?
//0x17	Static cargo
//0x18	Dies at small distance from player
//0x19	Asteroid
//0x1b	Space dust
//0x1c	
//0x1d	HS entrance cloud
//0x1e	HS cloud remnant
//0x1f	Request launch
//0x20	Docked/landed - waiting for traffic control timeout
//0x21	Launching
//0x23	Docking/landing
//0x24	Docked/landed

//Object types:	Stores ship table index for non-pirate?
//
//0x1		ship after esc. capsule
//0xfa	cargo
//0xfb 	pirate
//0xfd	missile
//0xfe	HS cloud
//0xff 	player
//
//flags:
//
//0x7		light index
//0x8		light flag
//0x10	starport/station? - dockable object
//0x20	starport (else station)
//0x40	open air?
//0x80	complex object
//
//laser flags:
//
//0x1		shields hit
//0x2		laser fired
//0x4		front laser
//0x8		rear laser
//0x10	turret laser
//0x20	ecm activated
//0x40	energy bomb activated
//
//Laser types:
//
//0x88	1MW pulse
//0xa0	1MW beam laser