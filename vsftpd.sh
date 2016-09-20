#
# vsftpd  this shell script takes cares of starting and stopping standalone vsftpd


. /etc/rc.d/init.d/functions

. /etc/sysconfig/network

RETVAL=0
prog="vsftpd"

start() {
 # start daemons
 [ -x /usr/sbin/vsftpd ] || exit 4
 CONFS=`ls /etc/vsftpd/*.conf 2>/dev/null`
 [ -z "$CONFS" ] && exit 6
 for i in $CONFS; do
	site=`basename $i .conf`
	echo -n $"Starting $prog for $site:"
	daemon /usr/sbin/vsftpd $i
	RETVAL=$?
	[ $RETVAL -eq 0 ] && touch /var/lock/subsys/$prog
	echo
 done
 return $RETVAL
}

stop() {
 # stop daemon
 echo -n $"shutting down $prog"
 killproc $prog
 RETVAL=$?
 [ $RETVAL -eq 0 ] && rm /var/lock/subsys/$prog
 return $RETVAL
}

case "$1" in
  start)
	start
	;;
  stop)
	stop
	;;
  *)
	echo "$usage"
	exit 2
esac
