/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PROTO_H_RPCGEN
#define _PROTO_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


#define CARTEIRO_RPC 11111
#define carteiro_universal_data_transport 1

#if defined(__STDC__) || defined(__cplusplus)
#define send_message 1
extern  enum clnt_stat send_message_1(char **, int *, CLIENT *);
extern  bool_t send_message_1_svc(char **, int *, struct svc_req *);
#define get_message 2
extern  enum clnt_stat get_message_1(char **, char **, CLIENT *);
extern  bool_t get_message_1_svc(char **, char **, struct svc_req *);
#define send_image 3
extern  enum clnt_stat send_image_1(char **, int *, CLIENT *);
extern  bool_t send_image_1_svc(char **, int *, struct svc_req *);
#define get_image 4
extern  enum clnt_stat get_image_1(char **, char **, CLIENT *);
extern  bool_t get_image_1_svc(char **, char **, struct svc_req *);
#define send_audio 5
extern  enum clnt_stat send_audio_1(char **, int *, CLIENT *);
extern  bool_t send_audio_1_svc(char **, int *, struct svc_req *);
#define get_audio 6
extern  enum clnt_stat get_audio_1(char **, char **, CLIENT *);
extern  bool_t get_audio_1_svc(char **, char **, struct svc_req *);
#define list_data 7
extern  enum clnt_stat list_data_1(char **, char **, CLIENT *);
extern  bool_t list_data_1_svc(char **, char **, struct svc_req *);
#define get_data 8
extern  enum clnt_stat get_data_1(char **, char **, CLIENT *);
extern  bool_t get_data_1_svc(char **, char **, struct svc_req *);
#define the_news 9
extern  enum clnt_stat the_news_1(void *, char **, CLIENT *);
extern  bool_t the_news_1_svc(void *, char **, struct svc_req *);
extern int carteiro_rpc_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define send_message 1
extern  enum clnt_stat send_message_1();
extern  bool_t send_message_1_svc();
#define get_message 2
extern  enum clnt_stat get_message_1();
extern  bool_t get_message_1_svc();
#define send_image 3
extern  enum clnt_stat send_image_1();
extern  bool_t send_image_1_svc();
#define get_image 4
extern  enum clnt_stat get_image_1();
extern  bool_t get_image_1_svc();
#define send_audio 5
extern  enum clnt_stat send_audio_1();
extern  bool_t send_audio_1_svc();
#define get_audio 6
extern  enum clnt_stat get_audio_1();
extern  bool_t get_audio_1_svc();
#define list_data 7
extern  enum clnt_stat list_data_1();
extern  bool_t list_data_1_svc();
#define get_data 8
extern  enum clnt_stat get_data_1();
extern  bool_t get_data_1_svc();
#define the_news 9
extern  enum clnt_stat the_news_1();
extern  bool_t the_news_1_svc();
extern int carteiro_rpc_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PROTO_H_RPCGEN */
