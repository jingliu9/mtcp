#! /bin/bash

MTCP_LIBS="-lgmp -lpthread -lrte_acl -lrte_bitratestats -lrte_cfgfile -lrte_cmdline -lrte_cryptodev -lrte_distributor -lrte_eal -lrte_efd -lrte_ethdev -lrte_eventdev -lrte_gro -lrte_hash -lrte_ip_frag -lrte_jobstats -lrte_kni -lrte_kvargs -lrte_latencystats -lrte_lpm -lrte_mbuf -lrte_mempool_ring -lrte_mempool -lrte_mempool_stack -lrte_meter -lrte_metrics -lrte_net -lrte_pdump -lrte_pipeline -lrte_pmd_af_packet -lrte_pmd_ark -lrte_pmd_avp -lrte_pmd_bnxt -lrte_pmd_bond -lrte_pmd_crypto_scheduler -lrte_pmd_cxgbe -lrte_pmd_e1000 -lrte_pmd_ena -lrte_pmd_enic -lrte_pmd_failsafe -lrte_pmd_fm10k -lrte_pmd_i40e -lrte_pmd_ixgbe -lrte_pmd_kni -lrte_pmd_lio -lrte_pmd_nfp -lrte_pmd_null_crypto -lrte_pmd_null -lrte_pmd_octeontx_ssovf -lrte_pmd_qede -lrte_pmd_ring -lrte_pmd_sfc_efx -lrte_pmd_skeleton_event -lrte_pmd_sw_event -lrte_pmd_tap -lrte_pmd_thunderx_nicvf -lrte_pmd_vhost -lrte_pmd_virtio -lrte_pmd_vmxnet3_uio -lrte_port -lrte_power -lrte_reorder -lrte_ring -lrte_sched -lrte_table -lrte_timer -lrte_vhost -ldpdk"
MTCP_DIR=${HOME}/mtcp/

CUR_DIR=`pwd`

gcc -shared -o libmtcp.so mtcp/src/*.o -L${MTCP_DIR}/dpdk-17.08/x86_64-native-linuxapp-gcc/lib ${MTCP_LIBS}  -lgmp -Wl,-rpath=${MTCP_DIR}/dpdk-17.08/x86_64-native-linuxapp-gcc/lib/
