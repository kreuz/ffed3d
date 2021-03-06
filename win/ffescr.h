#include "lua/lua.hpp"

typedef int (*CFunction) (void);

class scriptSystem
{
	static scriptSystem* _self;
//METHODS
public:
	static scriptSystem* getSingleton (void);
	void FreeInst (void);

	int doScript (char* scriptName);
	int doString (char* string);
	const char* getLastError (void);
	char* getLogString (int id);
	int getLogCount (void);

	int doPreLaunchScripts();
	int doAutoScripts();

	//LUA METHODS
	static int randomize (lua_State* L);
	static int setColor (lua_State *L);
	static int print (lua_State *L);
	static int math_sqrt (lua_State *L);
	static int logic_and (lua_State *L);
	static int logic_shiftright (lua_State *L);
	static int logic_shiftleft (lua_State *L);
	static void *nonLua[256];
	static char *nonLuaScr[256];

	//LUA PUSHING METHODS
	void newInteger (__int64 arg);
	void newNumber (double arg);
	void newString (char* arg);
	void newBool (bool arg);
	void newFunction (CFunction func);
	void registerVariable (char* varName);

	void newClass (void);
	void newChildInteger (char* varName, __int64 arg);
	void newChildNumber (char* varName, double arg);
	void newChildString (char* varName, char* arg);
	void newChildBool (char* varName, bool arg);
	void newChildFunction (char* funcName, CFunction arg);
	void registerClass (char* className);

	//LUA GET`SMETHOD
	char* getAsString (int arg_id);
	double getAsNumber (int arg_id);
	__int64 getAsInteger (int arg_id);
	int getFunction (char* funcName);
	
	char* getParentAsString (char* varName);
	double getParentAsNumber (char* varName);
	__int64 getParentAsInteger (char* varName);
	int getParenFunction (char* funcName);

	int callFunction (int argCount, int result);

	void AddToLog (char* text);
protected:
	scriptSystem (void);
	~scriptSystem (void);

	void BuildScriptsTable (void);

//VARIABLES
public:
protected:
	lua_State* luaVM;
	int _top;
	const char* error;

	size_t fs;
	size_t as;
	char** firstscripts;
	char** autoscripts;
	char** consoleText;
	int conTextCount;
};