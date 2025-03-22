#include "../lib/icmp.h"
#include "../lib/socket.h"
#include "../lib/un.h"

void
err_quit (const char *msg) {
        perror (msg);
        exit (0);
}

void
err_sys (const char *msg) {
        perror (msg);
        exit (0);
}

int
main (int argc, char **argv) {
        /*
         *	Example of working with glibc (getopt.h):
         *	https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
         *
         */

        int sockfd;
        int opt;

        struct sockaddr_in target;

        socket_work(&sockfd);

        while (1) {
                static struct option long_opt[]
                    = { { "help", no_argument, 0, 'h' },
                        { "ipv4", no_argument, 0, '4' },
                        { "ipv6", no_argument, 0, '6' },
                        { "fqdn", no_argument, 0, 'f' },
                        { 0, 0, 0, 0 } };

                int opt_index = 0;

                opt = getopt_long (argc, argv, "46f", long_opt, &opt_index);
                if (opt == -1)
                        break;
                switch (opt) {
                case 0:
                        if (long_opt[opt_index].flag != 0)
                                break;
                        printf ("%s", long_opt[opt_index].name);
                        if (optarg)
                                printf ("%s", optarg);
                        printf ("\n");
                        break;
                case 'h':
                        printf ("\t --ipv4, -4\n");
                        printf ("\t --ipv6, -6\n");
                        printf ("\t --fqdn, -f\n");
                        break;
                case '4':
                        printf ("IPv4 select\n");
                        break;
                case '6':
                        printf ("IPv6 select\n");
                        break;
                case 'f':

                        break;
                case '?':

                        break;
                default:
                        abort ();
                }
        }

        printf ("Trace to %s\n", argv[1]);

        for (int ttl = 1; ttl <= MAX_HOP; ttl++) {
                memset (&target, 0, sizeof (target));
                target.sin_family = AF_INET;
                if (inet_pton (AF_INET, argv[1], &target.sin_addr) <= 0) {
                        perror ("inet_pton");
                        exit (EXIT_FAILURE);
                }

                if (send_echo_req (sockfd, &target, getpid (), ttl, ttl) < 0) {
                        fprintf (stderr, "Failed to send packet\n");
                        continue;
                }

                int status = recv_echo_reply (sockfd, ttl);
                if (status < 0) {
                        fprintf (stderr, "Failed to receive packet\n");
                        continue;
                }
		sleep(1);
        }

        close (sockfd);
        exit (0);
}
