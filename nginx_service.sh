#!/bin/bash

#start up script. for the nginx web server
#chkconfig:

function_start_nginx(){
 printf "starting nginx .."
 ulimit -SHn 51200
 /usr/local/nginx/sbin/nginx 2>&1 > /dev/null && echo "OK" || echo "FAIL"
}

function_stop_nginx(){
 printf "stop nginx"
 ps -ef | grep "nginx:" | grep -v grep | awk '{print "kill -9" $2}' | /bin/sh && echo "OK" || echo "FAIL"
}

function_reload_nginx(){
 printf "reloading nginx ..."
 /usr/local/nginx/sbin/nginx -s reload && echo "OK" || echo "FAIL"
}

function_restart_nginx(){
 printf "restarting nginx.."
 function_stop_nginx
 sleep 3
 function_start_nginx
}

function_test(){
 /usr/local/nginx/sbin/nginx -t
}

if [ "$1" = "start" ]; then
function_start_nginx
elif [ "$1" = "stop" ]; then
function_stop_nginx
elif [ "$1" = "reload" ]; then
function_reload_nginx
elif [ "$1" = "restart" ]; then
function_restart_nginx
elif [ "$1" = "test" ]; then
function_test
else
printf "usage: nginx {start|stop|restart|reload|test} \n"
fi

