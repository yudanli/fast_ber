/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Simple"
 * 	found in "/home/styler/git/fast_ber/testfiles/simple5.asn"
 * 	`asn1c -S /home/styler/git/fast_ber/3rd_party/asn1c/skeletons -fno-constraints -fno-include-deps`
 */

#include "Child.h"

static asn_TYPE_member_t asn_MBR_list_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (4 << 2)),
		0,
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		""
		},
};
static const ber_tlv_tag_t asn_DEF_list_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_list_specs_3 = {
	sizeof(struct list),
	offsetof(struct list, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_list_3 = {
	"list",
	"list",
	SEQUENCE_OF_free,
	SEQUENCE_OF_print,
	SEQUENCE_OF_constraint,
	SEQUENCE_OF_decode_ber,
	SEQUENCE_OF_encode_der,
	SEQUENCE_OF_decode_xer,
	SEQUENCE_OF_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_list_tags_3,
	sizeof(asn_DEF_list_tags_3)
		/sizeof(asn_DEF_list_tags_3[0]) - 1, /* 1 */
	asn_DEF_list_tags_3,	/* Same as above */
	sizeof(asn_DEF_list_tags_3)
		/sizeof(asn_DEF_list_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_list_3,
	1,	/* Single element */
	&asn_SPC_list_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_Child_1[] = {
	{ ATF_POINTER, 1, offsetof(struct Child, meaning_of_life),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"meaning-of-life"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Child, list),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_list_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"list"
		},
};
static const ber_tlv_tag_t asn_DEF_Child_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Child_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* meaning-of-life */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* list */
};
static asn_SEQUENCE_specifics_t asn_SPC_Child_specs_1 = {
	sizeof(struct Child),
	offsetof(struct Child, _asn_ctx),
	asn_MAP_Child_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* Start extensions */
	3	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_Child = {
	"Child",
	"Child",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_Child_tags_1,
	sizeof(asn_DEF_Child_tags_1)
		/sizeof(asn_DEF_Child_tags_1[0]), /* 1 */
	asn_DEF_Child_tags_1,	/* Same as above */
	sizeof(asn_DEF_Child_tags_1)
		/sizeof(asn_DEF_Child_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_Child_1,
	2,	/* Elements count */
	&asn_SPC_Child_specs_1	/* Additional specs */
};

