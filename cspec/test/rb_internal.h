#ifndef RARG_RUBY_INTERNAL
	#define RARG_RUBY_INTERNAL

	typedef struct rb_thread_struct
	{
			VALUE self;
			rb_vm_t *vm;

			/* execution information */
			VALUE *stack;		/* must free, must mark */
			unsigned long stack_size;
			rb_control_frame_t *cfp;
			int safe_level;
			int raised_flag;
			VALUE last_status; /* $? */

			/* passing state */
			int state;

			/* for rb_iterate */
			const rb_block_t *passed_block;

			/* for bmethod */
			const rb_method_entry_t *passed_me;

			/* for load(true) */
			VALUE top_self;
			VALUE top_wrapper;

			/* eval env */
			rb_block_t *base_block;

			VALUE *local_lfp;
			VALUE local_svar;

			/* thread control */
			rb_thread_id_t thread_id;
			enum rb_thread_status status;
			int priority;
			int slice;

			native_thread_data_t native_thread_data;
			void *blocking_region_buffer;

			VALUE thgroup;
			VALUE value;

			VALUE errinfo;
			VALUE thrown_errinfo;
			int exec_signal;

			int interrupt_flag;
			rb_thread_lock_t interrupt_lock;
			struct rb_unblock_callback unblock;
			VALUE locking_mutex;
			struct rb_mutex_struct *keeping_mutexes;
			int transition_for_lock;

			struct rb_vm_tag *tag;
			struct rb_vm_protect_tag *protect_tag;

			int parse_in_eval;
			int mild_compile_error;

			/* storage */
			st_table *local_storage;
	#if USE_VALUE_CACHE
			VALUE value_cache[RUBY_VM_VALUE_CACHE_SIZE + 1];
			VALUE *value_cache_ptr;
	#endif

			struct rb_thread_struct *join_list_next;
			struct rb_thread_struct *join_list_head;

			VALUE first_proc;
			VALUE first_args;
			VALUE (*first_func)(ANYARGS);

			/* for GC */
			VALUE *machine_stack_start;
			VALUE *machine_stack_end;
			size_t machine_stack_maxsize;
	#ifdef __ia64
			VALUE *machine_register_stack_start;
			VALUE *machine_register_stack_end;
			size_t machine_register_stack_maxsize;
	#endif
			jmp_buf machine_regs;
			int mark_stack_len;

			/* statistics data for profiler */
			VALUE stat_insn_usage;

			/* tracer */
			rb_event_hook_t *event_hooks;
			rb_event_flag_t event_flags;
			int tracing;

			/* fiber */
			VALUE fiber;
			VALUE root_fiber;
			rb_jmpbuf_t root_jmpbuf;

			/* misc */
			int method_missing_reason;
			int abort_on_exception;
	#ifdef USE_SIGALTSTACK
			void *altstack;
	#endif
	} rb_thread_t;

#endif
