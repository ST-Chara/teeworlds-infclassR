/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_MAPITEMS_H
#define GAME_MAPITEMS_H

// layer types
enum
{
	LAYERTYPE_INVALID=0,
	LAYERTYPE_GAME,
	LAYERTYPE_TILES,
	LAYERTYPE_QUADS,
	// LAYERTYPE_FRONT,
	// LAYERTYPE_TELE,
	// LAYERTYPE_SPEEDUP,
	// LAYERTYPE_SWITCH,
	// LAYERTYPE_TUNE,
	LAYERTYPE_SOUNDS_DEPRECATED = 9, // deprecated! do not use this, this is just for compatibility reasons
	LAYERTYPE_SOUNDS,


	MAPITEMTYPE_VERSION=0,
	MAPITEMTYPE_INFO,
	MAPITEMTYPE_IMAGE,
	MAPITEMTYPE_ENVELOPE,
	MAPITEMTYPE_GROUP,
	MAPITEMTYPE_LAYER,
	MAPITEMTYPE_ENVPOINTS,
	MAPITEMTYPE_SOUND,
	// High map item type numbers suggest that they use the alternate
	// format with UUIDs. See src/engine/shared/datafile.cpp for some of
	// the implementation.

	CURVETYPE_STEP=0,
	CURVETYPE_LINEAR,
	CURVETYPE_SLOW,
	CURVETYPE_FAST,
	CURVETYPE_SMOOTH,
	NUM_CURVETYPES,

	// game layer tiles
	TILE_ENTITY_NULL=0,
	TILE_ENTITY_SPAWN_RED,
	TILE_ENTITY_SPAWN_BLUE,
	TILE_ENTITY_FLAGSTAND_RED,
	TILE_ENTITY_FLAGSTAND_BLUE,
	TILE_ENTITY_ARMOR,
	TILE_ENTITY_HEALTH,
	TILE_ENTITY_WEAPON_SHOTGUN,
	TILE_ENTITY_WEAPON_GRENADE,
	TILE_ENTITY_POWERUP_NINJA,
	TILE_ENTITY_WEAPON_LASER,

	TILE_PHYSICS_AIR=0,
	TILE_PHYSICS_SOLID=1,
	TILE_PHYSICS_NOHOOK=3,
	
	ZONE_NULL=0,
	ZONE_TELE_NOWITCH=1,
	ZONE_TELE_NOSCIENTIST,
	
	ZONE_DAMAGE_DEATH=1,
	ZONE_DAMAGE_DEATH_NOUNDEAD,
	ZONE_DAMAGE_DEATH_INFECTED,
	ZONE_DAMAGE_INFECTION,

	ZONE_BONUS_BONUS=1,
	
	TILEFLAG_VFLIP=1,
	TILEFLAG_HFLIP=2,
	TILEFLAG_OPAQUE=4,
	TILEFLAG_ROTATE=8,

	LAYERFLAG_DETAIL=1,
	TILESLAYERFLAG_PHYSICS=1,
	TILESLAYERFLAG_ENTITY=2,
	TILESLAYERFLAG_ZONE=4,

	ENTITY_OFFSET=255-16*4,
};

enum DD_TILE_TELE
{
	TILE_TELEINEVIL = 10,
	TILE_TELEINWEAPON = 14,
	TILE_TELEINHOOK = 15,
	TILE_TELEIN = 26,
	TILE_TELEOUT = 27,
};

struct CPoint
{
	int x, y; // 22.10 fixed point
};

struct CColor
{
	int r, g, b, a;
};

struct CQuad
{
	CPoint m_aPoints[5];
	CColor m_aColors[4];
	CPoint m_aTexcoords[4];

	int m_PosEnv;
	int m_PosEnvOffset;

	int m_ColorEnv;
	int m_ColorEnvOffset;
};

class CTile
{
public:
	unsigned char m_Index;
	unsigned char m_Flags;
	unsigned char m_Skip;
	unsigned char m_Reserved;
};

struct CMapItemInfo
{
	int m_Version;
	int m_Author;
	int m_MapVersion;
	int m_Credits;
	int m_License;
} ;

struct CMapItemImage
{
	int m_Version;
	int m_Width;
	int m_Height;
	int m_External;
	int m_ImageName;
	int m_ImageData;
} ;

struct CMapItemGroup_v1
{
	int m_Version;
	int m_OffsetX;
	int m_OffsetY;
	int m_ParallaxX;
	int m_ParallaxY;

	int m_StartLayer;
	int m_NumLayers;
} ;


struct CMapItemGroup : public CMapItemGroup_v1
{
	enum { CURRENT_VERSION=3 };

	int m_UseClipping;
	int m_ClipX;
	int m_ClipY;
	int m_ClipW;
	int m_ClipH;

	int m_aName[3];
} ;

struct CMapItemLayer
{
	int m_Version;
	int m_Type;
	int m_Flags;
} ;

struct CMapItemLayerTilemap
{
	CMapItemLayer m_Layer;
	int m_Version;

	int m_Width;
	int m_Height;
	int m_Flags;

	CColor m_Color;
	int m_ColorEnv;
	int m_ColorEnvOffset;

	int m_Image;
	int m_Data;

	int m_aName[3];

	// DDRace

	int m_Tele;
} ;

struct CMapItemLayerQuads
{
	CMapItemLayer m_Layer;
	int m_Version;

	int m_NumQuads;
	int m_Data;
	int m_Image;

	int m_aName[3];
} ;

struct CMapItemVersion
{
	int m_Version;
} ;

struct CEnvPoint
{
	int m_Time; // in ms
	int m_Curvetype;
	int m_aValues[4]; // 1-4 depending on envelope (22.10 fixed point)

	bool operator<(const CEnvPoint &Other) { return m_Time < Other.m_Time; }
} ;

struct CMapItemEnvelope_v1
{
	int m_Version;
	int m_Channels;
	int m_StartPoint;
	int m_NumPoints;
	int m_aName[8];
} ;

struct CMapItemEnvelope : public CMapItemEnvelope_v1
{
	enum { CURRENT_VERSION=2 };
	int m_Synchronized;
};

struct CSoundShape
{
	enum
	{
		SHAPE_RECTANGLE = 0,
		SHAPE_CIRCLE,
		NUM_SHAPES,
	};

	struct CRectangle
	{
		int m_Width, m_Height; // fxp 22.10
	};

	struct CCircle
	{
		int m_Radius;
	};

	int m_Type;

	union
	{
		CRectangle m_Rectangle;
		CCircle m_Circle;
	};
};

struct CSoundSource
{
	CPoint m_Position;
	int m_Loop;
	int m_Pan; // 0 - no panning, 1 - panning
	int m_TimeDelay; // in s
	int m_Falloff; // [0,255] // 0 - No falloff, 255 - full

	int m_PosEnv;
	int m_PosEnvOffset;
	int m_SoundEnv;
	int m_SoundEnvOffset;

	CSoundShape m_Shape;
};

struct CMapItemLayerSounds
{
	enum
	{
		CURRENT_VERSION = 2
	};

	CMapItemLayer m_Layer;
	int m_Version;

	int m_NumSources;
	int m_Data;
	int m_Sound;

	int m_aName[3];
};

struct CMapItemSound
{
	int m_Version;

	int m_External;

	int m_SoundName;
	int m_SoundData;
	int m_SoundDataSize;
};

// DDRace

class CTeleTile
{
public:
	unsigned char m_Number;
	unsigned char m_Type;
};

#endif
