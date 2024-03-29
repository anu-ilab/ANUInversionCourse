#ifndef forwardmodel_mpi_h
#define forwardmodel_mpi_h

#include <rjmcmc/rjmcmc_config.h>
#include <rjmcmc/forwardmodel.h>

#if defined(HAVE_MPI_H)

resultsetfm_t *
MPI_single_forwardmodel(int burnin,
			int total, 
			rjmcmc_uniform_rand_t random,
			rjmcmc_normal_rand_t normal,
			int nparameters,
			const forwardmodelparameter_t *parameters,
			single_fm_likelihood_t lp,
			void *user_arg,
			int samples,
			double credible_interval,
			int results,
			int mpisize,
			int mpirank,
			int root,
			MPI_Comm comm);

resultsetfm_t *
MPI_single_forwardmodel_hierarchical(int burnin,
				     int total, 
				     rjmcmc_uniform_rand_t random,
				     rjmcmc_normal_rand_t normal,
				     int nparameters,
				     const forwardmodelparameter_t *parameters,
				     int nhierarchicalparameters,
				     const forwardmodelparameter_t *hierarchicalparameters,
				     single_fm_likelihood_hierarchical_t lp,
				     void *user_arg,
				     int samples,
				     double credible_interval,
				     int results,
				     int mpisize,
				     int mpirank,
				     int root,
				     MPI_Comm comm);

resultset1dfm_t *
MPI_part1d_forwardmodel(int burnin,
			int total,
			int minpart,
			int maxpart,
			double minx,
			double maxx,
			int xsamples,
			int ysamples,
			double credible_interval,
			double pd,
			rjmcmc_uniform_rand_t random,
			rjmcmc_normal_rand_t normal,
			int nglobalparameters,
			const forwardmodelparameter_t *global_parameters,
			int nlocalparameters,
			const forwardmodelparameter_t *local_parameters,
			part1d_fm_likelihood_t lp,
			void *user_arg,
			int results,
			int mpisize,
			int mpirank,
			int root,
			MPI_Comm comm);

resultset1dfm_t *
MPI_part1d_forwardmodel_natural(int burnin,
				int total,
				int minpart,
				int maxpart,
				double xmin,
				double xmax,
				int xsamples,
				int ysamples,
				double credible_interval,
				double pd,
				rjmcmc_uniform_rand_t random,
				rjmcmc_normal_rand_t normal,
				int nglobalparameters,
				const forwardmodelparameter_t *global_parameters,
				int nlocalparameters,
				const forwardmodelparameter_t *local_parameters,
				part1d_fm_likelihood_t lp,
				void *user_arg,
				int results,
				int mpisize,
				int mpirank,
				int root,
				MPI_Comm comm);


resultset1dfm_t *
MPI_part1d_forwardmodel_hierarchical(int burnin,
				     int total,
				     int minpart,
				     int maxpart,
				     double minx,
				     double maxx,
				     int xsamples,
				     int ysamples,
				     double credible_interval,
				     double pd,
				     rjmcmc_uniform_rand_t random,
				     rjmcmc_normal_rand_t normal,
				     int nglobalparameters,
				     const forwardmodelparameter_t *
				     global_parameters,
				     int nlocalparameters,
				     const forwardmodelparameter_t *
				     local_parameters,
				     int nhierarchicalparameters,
				     const forwardmodelparameter_t *
				     hierarchical_parameters,
				     part1d_fm_hierarchical_likelihood_t lp,
				     void *user_arg,
				     int results,
				     int mpisize,
				     int mpirank,
				     int root,
				     MPI_Comm comm);

resultset1dfm_t *
MPI_part1d_forwardmodel_natural_hierarchical(int burnin,
					     int total,
					     int minpart,
					     int maxpart,
					     double xmin,
					     double xmax,
					     int xsamples,
					     int ysamples,
					     double credible_interval,
					     double pd,
					     rjmcmc_uniform_rand_t random,
					     rjmcmc_normal_rand_t normal,
					     int nglobalparameters,
					     const forwardmodelparameter_t *
					     global_parameters,
					     int nlocalparameters,
					     const forwardmodelparameter_t *
					     local_parameters,
					     int nhierarchicalparameters,
					     const forwardmodelparameter_t *
					     hierarchical_parameters,
					     part1d_fm_hierarchical_likelihood_t lp,
					     void *user_arg,
					     int results,
					     int mpisize,
					     int mpirank,
					     int root,
					     MPI_Comm comm);


resultset2dfm_t *
MPI_part2d_forwardmodel(int burnin,
			int total,
			int thin,
			int minpart,
			int maxpart,
			int initpart,
			double minx,
			double maxx,
			double miny,
			double maxy,
			int xsamples,
			int ysamples,
			int zsamples,
			double credible_interval,
			double pdx,
			double pdy,
			rjmcmc_uniform_rand_t random,
			rjmcmc_normal_rand_t normal,
			int nglobalparameters,
			const forwardmodelparameter_t *global_parameters,
			int nlocalparameters,
			const forwardmodelparameter_t *local_parameters,
			part2d_fm_likelihood_t lp,
			void *user_arg,
			int results,
			int mpisize,
			int mpirank,
			int root,
			MPI_Comm comm);

resultset2dfm_t *
MPI_part2d_forwardmodel_checkpoint(int burnin,
				   int total,
				   int thin,
				   int minpart,
				   int maxpart,
				   int initpart,
				   double minx,
				   double maxx,
				   double miny,
				   double maxy,
				   int xsamples,
				   int ysamples,
				   int zsamples,
				   double credible_interval,
				   double pdx,
				   double pdy,
				   rjmcmc_uniform_rand_t random,
				   rjmcmc_normal_rand_t normal,
				   int nglobalparameters,
				   const forwardmodelparameter_t *global_parameters,
				   int nlocalparameters,
				   const forwardmodelparameter_t *local_parameters,
				   part2d_fm_likelihood_t lp,
				   void *user_arg,
				   int results,
				   int checkpoint_interval,
				   const char *checkpoint_prefix,
				   int mpisize,
				   int mpirank,
				   int root,
				   MPI_Comm comm);

resultset2dfm_t *
MPI_part2d_forwardmodel_checkpoint_restart(rjmcmc_uniform_rand_t random,
					   rjmcmc_normal_rand_t normal,
					   part2d_fm_likelihood_t lp,
					   void *user_arg,
					   int checkpoint,
					   int checkpoint_interval,
					   const char *checkpoint_prefix,
					   int mpisize,
					   int mpirank,
					   int root,
					   MPI_Comm comm,
					   int *requested_results,
					   int *burnin,
					   int *total,
					   int *thin,
					   int *xsamples,
					   int *ysamples,
					   int *zsamples,
					   int *nprocesses,
					   int *maxpartitions,
					   double *xmin,
					   double *xmax,
					   double *ymin,
					   double *ymax,
					   double *credibleinterval,
					   int *nhierarchical,
					   int *nglobal,
					   int *nlocal,
					   forwardmodelparameter_t **local_parameters,
					   forwardmodelparameter_t **global_parameters);

resultset2dfm_t *
MPI_part2d_forwardmodel_restartable(const char *model_file_in_template,
				    const char *model_file_out_template,
				    int burnin,
				    int total,
				    int thin,
				    int minpart,
				    int maxpart,
				    int initpart,
				    double xmin,
				    double xmax,
				    double ymin,
				    double ymax,
				    int xsamples,
				    int ysamples,
				    int zsamples,
				    double credible_interval,
				    double pdx,
				    double pdy,
				    rjmcmc_uniform_rand_t random,
				    rjmcmc_normal_rand_t normal,
				    int nglobalparameters,
				    const forwardmodelparameter_t *
				    global_parameters,
				    int nlocalparameters,
				    const forwardmodelparameter_t *
				    local_parameters,
				    part2d_fm_likelihood_t lp,
				    void *user_arg,
				    int results,
				    int mpisize,
				    int mpirank,
				    int root,
				    MPI_Comm comm);

resultset2dfm_t *
MPI_part2d_forwardmodel_hierarchical(int burnin,
				     int total,
				     int thin,
				     int minpart,
				     int maxpart,
				     int initpart,
				     double minx,
				     double maxx,
				     double miny,
				     double maxy,
				     int xsamples,
				     int ysamples,
				     int zsamples,
				     double credible_interval,
				     double pdx,
				     double pdy,
				     rjmcmc_uniform_rand_t random,
				     rjmcmc_normal_rand_t normal,
				     int nglobalparameters,
				     const forwardmodelparameter_t *
				     global_parameters,
				     int nlocalparameters,
				     const forwardmodelparameter_t *
				     local_parameters,
				     int nhierarchicalparameters,
				     const forwardmodelparameter_t *
				     hierarchical_parameters,
				     part2d_fm_hierarchical_likelihood_t lp,
				     void *user_arg,
				     int results,
				     int mpisize,
				     int mpirank,
				     int root,
				     MPI_Comm comm);

resultset2dfm_t *
MPI_part2d_forwardmodel_hierarchical_restartable(const char *model_file_in_template,
						 const char *nodel_file_out_template,
						 int burnin,
						 int total,
						 int thin,
						 int minpart,
						 int maxpart,
						 int initpart,
						 double xmin,
						 double xmax,
						 double ymin,
						 double ymax,
						 int xsamples,
						 int ysamples,
						 int zsamples,
						 double credible_interval,
						 double pdx,
						 double pdy,
						 rjmcmc_uniform_rand_t random,
						 rjmcmc_normal_rand_t normal,
						 int nglobalparameters,
						 const forwardmodelparameter_t *
						 global_parameters,
						 int nlocalparameters,
						 const forwardmodelparameter_t *
						 local_parameters,
						 int nhierarchicalparameters,
						 const forwardmodelparameter_t *
						 hierarchical_parameters,
						 part2d_fm_hierarchical_likelihood_t lp,
						 void *user_arg,
						 int results,
						 int mpisize,
						 int mpirank,
						 int root,
						 MPI_Comm comm);

#endif /* HAVE_MPI_H */

#endif /* forwardmodel_mpi_h */
