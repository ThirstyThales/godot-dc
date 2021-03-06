public:
#ifdef BVH_VERBOSE
void _debug_recursive_print_tree(int p_tree_id) const {
	if (_root_node_id[p_tree_id] != BVHCommon::INVALID)
		_debug_recursive_print_tree_node(_root_node_id[p_tree_id]);
}

String _debug_aabb_to_string(const BVH_ABB &aabb) const {
	String sz = "(";
	sz += itos(-aabb.neg_min.x);
	sz += " ~ ";
	sz += itos(aabb.max.x);
	sz += ") (";

	sz += itos(-aabb.neg_min.y);
	sz += " ~ ";
	sz += itos(aabb.max.y);
	sz += ") (";

	sz += itos(-aabb.neg_min.z);
	sz += " ~ ";
	sz += itos(aabb.max.z);
	sz += ") ";

	Vector3 size = aabb.calculate_size();
	float vol = size.x * size.y * size.z;
	sz += "vol " + itos(vol);

	return sz;
}

void _debug_recursive_print_tree_node(uint32_t p_node_id, int depth = 0) const {
	const TNode &tnode = _nodes[p_node_id];

	String sz = "";
	for (int n = 0; n < depth; n++) {
		sz += "\t";
	}
	sz += itos(p_node_id);

	if (tnode.is_leaf()) {
		sz += " L";
		sz += itos(tnode.height) + " ";
		const TLeaf *leaf = node_get_leaf(tnode);

		sz += "[";
		for (int n = 0; n < leaf->num_items; n++) {
			if (n)
				sz += ", ";
			sz += "r";
			sz += itos(leaf->get_item_ref_id(n));
		}
		sz += "]  ";
	} else {
		sz += " N";
		sz += itos(tnode.height) + " ";
	}

	sz += _debug_aabb_to_string(tnode.aabb);
	print_line(sz);

	if (!tnode.is_leaf()) {
		for (int n = 0; n < tnode.num_children; n++) {
			_debug_recursive_print_tree_node(tnode.children[n], depth + 1);
		}
	}
}
#endif
