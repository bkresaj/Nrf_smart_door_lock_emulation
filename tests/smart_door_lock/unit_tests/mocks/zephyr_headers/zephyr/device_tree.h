#ifndef DEVICE_TREE_H_
#define DEVICE_TREE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DT_CAT(a1, a2) a1##a2
/** @brief Concatenation helper, 3 arguments */
#define DT_CAT3(a1, a2, a3) a1##a2##a3
/** @brief Concatenation helper, 4 arguments */
#define DT_CAT4(a1, a2, a3, a4) a1##a2##a3##a4
/** @brief Internal concatenation helper, 5 arguments */
#define DT_CAT5(a1, a2, a3, a4, a5) a1##a2##a3##a4##a5
/** @brief Concatenation helper, 6 arguments */
#define DT_CAT6(a1, a2, a3, a4, a5, a6) a1##a2##a3##a4##a5##a6
/** @brief concatenation helper, 7 arguments */
#define DT_CAT7(a1, a2, a3, a4, a5, a6, a7) a1##a2##a3##a4##a5##a6##a7
/** @brief concatenation helper, 8 arguments */
#define DT_CAT8(a1, a2, a3, a4, a5, a6, a7, a8) a1##a2##a3##a4##a5##a6##a7##a8

// real function
// #define DT_PROP(node_id, prop) DT_CAT3(node_id, _P_, prop)
// fake function
#define DT_PROP(node_id, prop) prop

// random value for DT_CHOSEN_
#define DT_CHOSEN_ 1
#define DT_CHOSEN(prop) DT_CAT(DT_CHOSEN_, prop)

#ifdef __cplusplus
}
#endif

#endif