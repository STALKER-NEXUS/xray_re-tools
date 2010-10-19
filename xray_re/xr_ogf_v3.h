#ifndef __GNUC__
#pragma once
#endif
#ifndef __XR_OGF_V3_H__
#define __XR_OGF_V3_H__

#include <vector>
#include "xr_ogf.h"

namespace xray_re {

class xr_ini_file;

class xr_ogf_v3: public xr_ogf {
public:
				xr_ogf_v3();
	virtual			~xr_ogf_v3();

	virtual void		clear();
	virtual void		load_ogf(xr_reader& r);

	void			set_ext_geom(const xr_vbuf_vec& ext_vbufs);

	virtual bool		hierarchical() const;
	virtual bool		skeletal() const;
	virtual bool		animated() const;
	virtual bool		progressive() const;
	virtual bool		versioned() const;

	virtual const xr_ibuf&	ib() const;
	virtual uint32_t	texture_l() const;
	virtual uint32_t	shader_l() const;

	uint32_t		ext_vb_index() const;
	uint32_t		ext_vb_offset() const;
	uint32_t		ext_vb_size() const;

public:
	struct bone_io;
	struct partition_io;
	struct motion_io;
	struct bone_motion_io;

protected:
	void	load_header(xr_reader& r);
	void	load_texture(xr_reader& r);
	void	load_texture_l(xr_reader& r);
	void	load_child_refs(xr_reader& r);
	void	load_bbox(xr_reader& r);
	void	load_vertices(xr_reader& r);
	void	load_indices(xr_reader& r);
	void	load_loddata(xr_reader& r);
	void	load_vcontainer(xr_reader& r);
	void	load_bsphere(xr_reader& r);
	void	load_children_l(xr_reader& r);
	void	load_s_bone_names(xr_reader& r);
	void	load_s_motions(xr_reader& r);
	void	load_dpatch(xr_reader& r);
	void	load_lods(xr_reader& r);
	void	load_children(xr_reader& r);
	void	load_s_smparams(xr_reader& r);
	void	load_s_smparams();
	void	load_motion_defs(xr_ini_file& ini, ogf3_motion_type motion_type, const char* motion_type_section);

	void	setup_ib0();

private:
	void	load_render_visual(xr_reader& r);
	void	load_visual(xr_reader& r);
	void	load_hierrarhy_visual(xr_reader& r);
	void	load_progressive_fixed_visual(xr_reader& r);
	void	load_kinematics(xr_reader& r);
	void	load_skeletonx(xr_reader& r);
	void	load_skeletonx_pm(xr_reader& r);
	void	load_skeletonx_st(xr_reader& r);
	void	load_detail_patch(xr_reader& r);
	void	load_cached(xr_reader& r);
	void	load_particle(xr_reader& r);
	void	load_progressive(xr_reader& r);

private:
	uint32_t	m_texture_l;	// OGF_TEXTURE_L
	uint32_t	m_shader_l;

	uint32_t	m_min_vertices;	// OGF_LODDATA
	uint32_t	m_min_indices;
	ogf3_vsplit*	m_vsplits;
	uint32_t	m_num_fix_faces;
	uint16_t*	m_fix_faces;
	xr_ibuf		m_ib0;		// proxy ib for max LOD

	uint32_t	m_ext_vb_index;	// OGF_VCONTAINER
	uint32_t	m_ext_vb_offset;
	uint32_t	m_ext_vb_size;
};

TYPEDEF_STD_VECTOR_PTR(xr_ogf_v3)

inline const xr_ibuf& xr_ogf_v3::ib() const { return progressive() ? m_ib0 : m_ib; }
inline uint32_t xr_ogf_v3::texture_l() const { return m_texture_l; }
inline uint32_t xr_ogf_v3::shader_l() const { return m_shader_l; }
inline uint32_t xr_ogf_v3::ext_vb_index() const { return m_ext_vb_index; }
inline uint32_t xr_ogf_v3::ext_vb_offset() const { return m_ext_vb_offset; }
inline uint32_t xr_ogf_v3::ext_vb_size() const { return m_ext_vb_size; }

} // end of namespace xray_re

#endif
